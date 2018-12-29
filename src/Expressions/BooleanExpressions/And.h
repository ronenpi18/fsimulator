//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_AND_H
#define PROG1PROJECT_AND_H


#include "../BinaryExpression.h"

class And : public BinaryExpression {

public:

    // constructor.
    And(Expression* left, Expression* right):
        BinaryExpression("&&", left, right) {}

    // the implementation of operation - And.
    double operation(double var1, double var2) {return var1 && var2;};
};


#endif //PROG1PROJECT_AND_H
