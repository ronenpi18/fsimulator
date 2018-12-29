//
// created by omri & gal on 12/17/18.
//

#ifndef PROG1PROJECT_IfCOMMAND_H
#define PROG1PROJECT_IfCOMMAND_H

#include "../Command.h"
#include "ConditionParser.h"

class IfCommand: public ConditionParser{
public:
    // constructor:
    IfCommand(vector<string>& v):
    ConditionParser(v) {};

    void doCommand() override;



};


#endif //PROG1PROJECT_IfCOMMAND_H
