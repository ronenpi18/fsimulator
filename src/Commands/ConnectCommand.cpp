
#include "ConnectCommand.h"
#include <stdexcept>
#include "../Utils.h"
#include "../Databases/SymbolsDB.h"
#include "../Databases/ConstsDB.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

using namespace std;

void task(vector<string>& args);

void ConnectCommand::doCommand() {

    struct hostent *server;
    int port;
    try {

        if(args.size() < 2)
            throw;

            // get ip as string form args.
        server = gethostbyname(args[0].c_str());

        // extracting next expression from args using shunting yard.
        // deleting the ip, and sends the rest to shunting yard.
        int skip = 0;
        if (args[1] == ",")
            skip  = 1;
        args.erase(args.begin(), args.begin() + skip + 1);

        // calculating the port from the expression.

        vector<Expression*> extractedExpressions = Utils::SplitCommaArgsToExpressions(args);
        if (extractedExpressions.size() != 1)
            throw;

        port = extractedExpressions[0]->calculate();

        for(Expression* pe: extractedExpressions)
            delete pe;




    }
    catch (...){
        throw ServerException("failed connecting to server, invalid argument IP or Port is not representing an int");
    }

    // connecting to server in port port.
    connectToServer(server, port);

}

void ConnectCommand::disconnect() {
    if (_socketfd != 0)
        close(_socketfd);
}

ConnectCommand::~ConnectCommand() {
    disconnect();
}

/*
* task1 will be responsible of opening a client at the specified ip and port (two of the argumnets in args).
* this client socket will allow us to change variables in the fightgear and update values according to the information
* we will get from the final client. this task will run in it's own thread, simultaneously with another threads so that
* we could run our program faster while making io requests.
*/
void ConnectCommand::connectToServer(struct  hostent *server, int port) {

    int sockfd,  n;
    struct sockaddr_in serv_addr;

    char buffer[256];


    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        throw ServerException("ERROR opening socket");
        
    }


    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        throw ServerException("ERROR connecting");
        
    }

    /* Now ask for a message from the user, this message
       * will be read by server
    */

    SymbolsDB::setSocket(sockfd);



}

bool ConnectCommand::anotherArg(string &current) {

    // get until end of line.
    return current != ConstsDB::ENDLINE_KEYWORD;
}

bool ConnectCommand::goBackArg(string &current) {
    // open data server command don't need to go back to read before the keyword.
    return false;
}
