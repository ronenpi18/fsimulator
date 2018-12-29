//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_SMALLER_EQUALS_H
#define PROG1PROJECT_SMALLER_EQUALS_H


#include "../BinaryExpression.h"

class SmallerEquals : public BinaryExpression {

public:

    // constructor.
    SmallerEquals(Expression* left, Expression* right):
        BinaryExpression("<=", left, right) {}

    // the implementation of operation - SmallerEquals.
    double operation(double var1, double var2) {return var1 >= var2;};
};


#endif //PROG1PROJECT_SMALLER_EQUALS_H
