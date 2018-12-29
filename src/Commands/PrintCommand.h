//
// created
//

#ifndef PROG1PROJECT_PRINTCOMMAND_H
#define PROG1PROJECT_PRINTCOMMAND_H

#include "../Command.h"

/**
 * PrintCommand class-
 * Command that prints a message.
 */
class PrintCommand : public Command{

protected:

    vector<string>& args;

public:
    // constructor:
    PrintCommand(vector<string>& v):
        args(v) {};

    bool anotherArg(string &current) override;

    void doCommand() override;

    bool goBackArg(string &current) override;


};


#endif //PROG1PROJECT_PRINTCOMMAND_H
