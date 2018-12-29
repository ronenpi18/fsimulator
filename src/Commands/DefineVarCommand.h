

#ifndef PROG1PROJECT_DEFINEVARCOMMAND_H
#define PROG1PROJECT_DEFINEVARCOMMAND_H

#include "../Command.h"

class DefineVarCommand : public Command{
private:
    int _internalUseN = 1;

protected:

    vector<string>& args;

public:
    // constructor:
    DefineVarCommand(vector<string>& v):
    args(v) {};

    bool goBackArg(string &current) override;

    void doCommand() override;

    bool anotherArg(string &current) override;


};


#endif //PROG1PROJECT_DEFINEVARCOMMAND_H
