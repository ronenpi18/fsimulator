//
// created by omri & gal on 12/24/18.
//

#ifndef PROG1PROJECT_SLEEPCOMMAND_H
#define PROG1PROJECT_SLEEPCOMMAND_H


#include "../Command.h"

class SleepCommand: public Command {

protected:
    vector<string>& args;

public:

    // constructor:
    SleepCommand(vector<string>& v):
        args(v) {}

    void doCommand() override;

    bool anotherArg(string &current) override;

    bool goBackArg(string &current) override;
};


#endif //PROG1PROJECT_SLEEPCOMMAND_H
