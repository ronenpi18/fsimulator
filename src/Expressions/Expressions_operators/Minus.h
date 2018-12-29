//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_Minus_H
#define PROG1PROJECT_Minus_H


#include "../BinaryExpression.h"

class Minus : public BinaryExpression {

public:

    // constructor.
    Minus(Expression* left, Expression* right):
        BinaryExpression("-", left, right) {}

    // the implementation of operation - Minus.
    double operation(double var1, double var2) {return var1 - var2;};
};


#endif //PROG1PROJECT_Minus_H
