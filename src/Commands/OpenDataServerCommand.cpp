//
// created
//

#include "OpenDataServerCommand.h"
#include <stdexcept>
#include "../Utils.h"
#include "../Databases/SymbolsDB.h"
#include "../Databases/ConstsDB.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>
#include <iostream>
#include <fcntl.h>

using namespace std;

const vector<string> OpenDataServerCommand::_flightSymbols = {"\"/instrumentation/airspeed-indicator/indicated-speed-kt\"","\"/instrumentation/altimeter/indicated-altitude-ft\"","\"/instrumentation/altimeter/pressure-alt-ft\"","\"/instrumentation/attitude-indicator/indicated-pitch-deg\"","\"/instrumentation/attitude-indicator/indicated-roll-deg\"","\"/instrumentation/attitude-indicator/internal-pitch-deg\"","\"/instrumentation/attitude-indicator/internal-roll-deg\"","\"/instrumentation/encoder/indicated-altitude-ft\"","\"/instrumentation/encoder/pressure-alt-ft\"","\"/instrumentation/gps/indicated-altitude-ft\"","\"/instrumentation/gps/indicated-ground-speed-kt\"","\"/instrumentation/gps/indicated-vertical-speed\"","\"/instrumentation/heading-indicator/indicated-heading-deg\"","\"/instrumentation/magnetic-compass/indicated-heading-deg\"","\"/instrumentation/slip-skid-ball/indicated-slip-skid\"","\"/instrumentation/turn-indicator/indicated-turn-rate\"","\"/instrumentation/vertical-speed-indicator/indicated-speed-fpm\"","\"/controls/flight/aileron\"","\"/controls/flight/elevator\"","\"/controls/flight/rudder\"","\"/controls/flight/flaps\"","\"/controls/engines/current-engine/throttle\"","\"/engines/engine/rpm\""};

void OpenDataServerCommand::openServer(int port) {


    int sockfd, newsockfd, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        throw ServerException("ERROR opening socket");
        
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    /* Now bind the host address using bind() call.*/
    if (::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        throw ServerException("ERROR on binding");
        
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    //fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

    if (newsockfd < 0) {
        throw ServerException("ERROR on accept");
        
    }

    _sockfd = newsockfd;

    // wait to first arguments from client flight simulator:
    getAllFlightSymbols();
}

void OpenDataServerCommand::closeServer() {
    if (_sockfd > 0) {
        close(_sockfd);
    }
}

OpenDataServerCommand::~OpenDataServerCommand() {
    _continueGetData = false;
    closeServer();
}

void OpenDataServerCommand::getAllFlightSymbols() {

    char buffer[1024];
    bzero(buffer, 1024);

    // wait for actual data to be recieved from flights simulator client.
    int n;
    do {
        n = read(_sockfd, buffer, 1024);
    } while (strlen(buffer) == 0);

    if (n < 0) {
        throw ServerException("ERROR reading from socket");
        
    }

    // translate the values from strings into a vector of string of double symbol values.
    string allValuesStrWithCommas(buffer);
    vector<string> allValuesStrNewLine = Utils::strSplit(allValuesStrWithCommas, '\n');
    vector<string> allValuesStr;

    bool found = false;
    for (int i = 0; i < allValuesStrNewLine.size(); i++) {

        allValuesStr = Utils::strSplit(allValuesStrNewLine[i], ',');
        if(allValuesStr.size() == allValuesStr.size()) {
                found = true;
                break;
        }

    }


    // if the number of recieved values is not like the number of requested numbers, throw exception.
    if (!found)
        throw FlightsServerException("Error occured on reciving sampled flights symbols values.");

    // translate the string values to double value.

    vector<double> allValuesDouble;
    for (int i = 0; i < allValuesStr.size(); i++) {
        allValuesDouble.push_back(Utils::to_number(allValuesStr[i]));
    }

    bool serverUp = false;

    // check that flights server is fully up, by checking that its not all 0 , so then the server isn't up yet.
    for (int i = 0; i < allValuesDouble.size(); i++) {
        if (allValuesDouble[i] != 0)
            serverUp = true;
    }

    // if server didn't up, sleep a 500 ms (0.5 second), and do the whole function again:
    if (!serverUp) {
        this_thread::sleep_for(chrono::milliseconds(500));
        getAllFlightSymbols();
        return;
    }


    // if its fine, sets the symbols at the symbol Table to be the values in allValuesDouble mathcing the order.

    for (int i = 0; i < OpenDataServerCommand::_flightSymbols.size(); i++) {
        SymbolsDB::setLocalSymbol(OpenDataServerCommand::_flightSymbols[i], allValuesDouble[i]);
    }
}

void OpenDataServerCommand::doCommand() {

    int port;
    double frequency;

    // tring to tanslate port and frequency to ints -from the args.
    try {

        // extracting next two expressions from the args.
        vector<Expression*> extractedExpressions = Utils::SplitCommaArgsToExpressions(args);
        if (extractedExpressions.size() != 2)
            throw BadArgumentsException("bad arguments on openDataServer");

        port = (int) extractedExpressions[0]->calculate();
        frequency = extractedExpressions[1]->calculate();
    }

        // chatches invalid argument of to_number if port or frequency are not ints.
    catch(const std::invalid_argument& e){

        throw ServerException("failed opening server, invalid argument PORT or RATE is not representing an int");
    }


    // open server at port, that reads reads frequency times a second.

    openServer(port);

    // open a thread that runs a loop of collecting data:

    thread getSymbolsLoop = thread(&OpenDataServerCommand::task, this, frequency);
    getSymbolsLoop.detach();
}

/*
* task1 will be responsible of opening a server at the specified port (one of the argumnets in args).
* from this server we will listen to the fightgear and update values according to the information
* he will deliver us. this task will run in it's own thread, simultaneously with another threads so that
* we could run our program faster while making io requests.
*/
void OpenDataServerCommand::task(int frequency) {

    // forever, sample all flight symbols.
    while(_continueGetData) {

        // get all flight symbols from the client - the simulator.
        const clock_t before = clock();
        getAllFlightSymbols();

        double commandTookThisTime = double(clock() - before);

        // wait time so that it will be Hz = 10 times a second.
        if (1/frequency - commandTookThisTime > 0)
            this_thread::sleep_for(chrono::duration<double>(1/frequency - commandTookThisTime));
    }

}


bool OpenDataServerCommand::anotherArg(string &current) {

    // get until end of line.
    return current != ConstsDB::ENDLINE_KEYWORD;
}

bool OpenDataServerCommand::goBackArg(string &current) {
    // open data server command don't need to go back to read before the keyword.
    return false;
}
