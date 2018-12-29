//
// created by omri & gal on 12/18/18.
//

#ifndef PROG1PROJECT_SEMICOLONCOMMAND_H
#define PROG1PROJECT_SEMICOLONCOMMAND_H

#include "../Command.h"

class SemicolonCommand: public Command{

protected:

    vector<string>& args;

public:
    SemicolonCommand(vector<string>& v):
        args(v) {}

    void doCommand() override {
        // do nothing as ;.
    }

    bool anotherArg(string &current) override {
        // ; command don't need no more arguments. it does nothing.
        return false;
    }

    bool goBackArg(string &current) override {
        // ; command don't need to go back before it. it does nothing.
        return false;
    }

};
#endif //PROG1PROJECT_SEMICOLONCOMMAND_H
