//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_BIGGER_H
#define PROG1PROJECT_BIGGER_H


#include "../BinaryExpression.h"

class Bigger : public BinaryExpression {

public:

    // constructor.
    Bigger(Expression* left, Expression* right):
        BinaryExpression(">", left, right) {}

    // the implementation of operation - Bigger.
    double operation(double var1, double var2) {return var1 > var2;};
};


#endif //PROG1PROJECT_BIGGER_H
