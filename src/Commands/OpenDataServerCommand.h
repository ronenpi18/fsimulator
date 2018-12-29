//
// created
//

#ifndef PROG1PROJECT_OPENDATASERVER_H
#define PROG1PROJECT_OPENDATASERVER_H

#include "../Command.h"
#include <string>
#include "../Sockets/FlightDataGetterSetter.h"


using namespace std;

class OpenDataServerCommand: public Command {
private:
    int _sockfd = 0;
    bool _continueGetData;


    // opens a server socket, that can recieve data from client - flight simulator.
    void openServer(int port);

    // close down the server:
    void closeServer();



protected:

    vector<string>& args;
public:

    // constructor:
    OpenDataServerCommand(vector<string>& v):
        args(v), _continueGetData(true) {};

    // command method:
        bool goBackArg(string &current) override;

    void doCommand() override;

    bool anotherArg(string &current) override;


    void task(int frequency);

// take all flight symbols from server to maps.
    void getAllFlightSymbols();

    // list of all symbolNames for flight.
    static const vector<string> _flightSymbols;

    ~OpenDataServerCommand();

};


#endif //PROG1PROJECT_OPENDATASERVER_H
