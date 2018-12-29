//
// created by omri & gal on 12/17/18.
//

#ifndef PROG1PROJECT_COMMANDEXPRESSION_H
#define PROG1PROJECT_COMMANDEXPRESSION_H

#include "Expression.h"
#include "Command.h"
/*
 * class CommandExpression made for adapting Command to be an Expression
 * without breaking interface serergation.
 * */
class CommandExpression: Expression {
private:
    Command* _command;

public:

    // constructor.
    CommandExpression(Command* c) :
        _command(c) {};

    // override:
    double calculate() override {
        try {
            _command->doCommand();
            return 1;
        } catch (exception e){
            return 0;
        }
    }

};


#endif //PROG1PROJECT_COMMANDEXPRESSION_H

