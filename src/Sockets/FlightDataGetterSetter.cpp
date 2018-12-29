//
// created by omri & gal on 12/22/18.
//

#include <strings.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "FlightDataGetterSetter.h"
#include "../Utils.h"
#include "../Exceptions.h"


double FlightDataGetterSetter::recieve(string message) {
    char buffer[256];

    bzero(buffer, 256);
    strcpy(buffer, message.c_str());
    strcpy(buffer + message.length(), "\r\n");

    /* Send message to the server */
    int n = write(_socketfd, buffer, strlen(buffer));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    /* Now read server response */
    bzero(buffer,256);
    n = read(_socketfd, buffer, 255);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
    // reutrn the double value the server sent.
    string answer = string(buffer);


    // extract the float part of the "x = '<double-part>' (double)" answer.
    vector<string> equalSplit = Utils::strSplit(answer, '=');
    if (equalSplit.size() < 2) {
        return recieve(message);
    }
    vector<string> parantethisSplit = Utils::strSplit(equalSplit[1], '\'');
    if (parantethisSplit.size() < 3)
        throw FlightsServerException("server sent somthing wrong formmatted.");
    string doublePart = parantethisSplit[1];
    return Utils::to_number(doublePart);
}

void FlightDataGetterSetter::send(string message) {
    char buffer[256];

    bzero(buffer, 256);
    strcpy(buffer, message.c_str());
    strcpy(buffer + message.length(), "\r\n");



    // wait for a user enters a command ment for the flightserver.


    /* Send message to the server */
    int n = write(_socketfd, buffer, strlen(buffer));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}
