//
// created by omri & gal on 12/22/18.
//

#ifndef PROG1PROJECT_FlightDataGetterSetter_H
#define PROG1PROJECT_FlightDataGetterSetter_H

#include <map>
#include <string>

using namespace std;

/**
 * this class is responsible for manaing sockets and sending messages through them.
 */
class FlightDataGetterSetter {

private:
    int _socketfd;

public:

    // constructor.
    FlightDataGetterSetter(int _socketfd) : _socketfd(_socketfd) {}

    // sends a message through the socket.
    double recieve(string message);

    void send(string message);
};


#endif //PROG1PROJECT_FlightDataGetterSetter_H
