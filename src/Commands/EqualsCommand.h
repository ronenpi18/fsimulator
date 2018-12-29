//
// created by omri & gal on 12/18/18.
//

#ifndef PROG1PROJECT_EQUALSCOMMAND_H
#define PROG1PROJECT_EQUALSCOMMAND_H

#include "../Command.h"

class EqualsCommand: public Command {
private:
    int _internalUseN = 2;

protected:

    vector<string>& args;
public:
    // constructor:
    EqualsCommand(vector<string>& v):
    args(v) {};

    void doCommand() override;

    bool anotherArg(string &current) override;

    bool goBackArg(string &current) override;



};


#endif //PROG1PROJECT_EQUALSCOMMAND_H
