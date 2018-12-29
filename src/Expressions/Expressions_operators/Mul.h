//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_Mul_H
#define PROG1PROJECT_Mul_H


#include "../BinaryExpression.h"

class Mul : public BinaryExpression {

public:

    // constructor.
    Mul(Expression* left, Expression* right):
        BinaryExpression("*", left, right) {}

    // the implementation of operation - Mul.
    double operation(double var1, double var2) {return var1 * var2;};

};


#endif //PROG1PROJECT_Mul_H
