//
// created by Chenon 12/10/18.
//

#ifndef PROG1PROJECT_NOTEQUALS_H
#define PROG1PROJECT_NOTEQUALS_H


#include "../BinaryExpression.h"

class NotEquals : public BinaryExpression {

public:

    // constructor.
    NotEquals(Expression* left, Expression* right):
        BinaryExpression("!=", left, right) {}

    // the implementation of operation - NotEquals.
    double operation(double var1, double var2) {return var1 != var2;};
};


#endif //PROG1PROJECT_NOTEQUALS_H
