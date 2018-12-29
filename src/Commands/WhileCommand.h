//
// created by omri & gal on 12/17/18.
//

#ifndef PROG1PROJECT_WHILECOMMAND_H
#define PROG1PROJECT_WHILECOMMAND_H

#include "../Command.h"
#include "ConditionParser.h"

class WhileCommand :public ConditionParser{

public:
    // constructor:
    WhileCommand(vector<string>& v):
    ConditionParser(v) {};

    void doCommand() override;


};


#endif //PROG1PROJECT_WHILECOMMAND_H
