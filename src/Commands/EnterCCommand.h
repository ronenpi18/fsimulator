//
// created by omri & gal on 12/18/18.
//

#ifndef PROG1PROJECT_ENTERCCOMMAND
#define PROG1PROJECT_ENTERCCOMMAND

#include "../Command.h"
#include <thread>
class EnterCCommand: public Command{

protected:

    vector<string>& args;

public:
    EnterCCommand(vector<string>& v):
        args(v) {}

    void doCommand() override {

        // wait to a char enter from console.
        getchar();
    }

    bool anotherArg(string &current) override {
        // ; command don't need no more arguments.
        return false;
    }

    bool goBackArg(string &current) override {
        // ; command don't need to go back before it.
        return false;
    }

    // clonable:
};
#endif //PROG1PROJECT_ENTERCCOMMAND
