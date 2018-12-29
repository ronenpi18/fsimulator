//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_Pow_H
#define PROG1PROJECT_Pow_H


#include "../BinaryExpression.h"
#include <cmath>
class Pow : public BinaryExpression {

public:

    // constructor.
    Pow(Expression* left, Expression* right):
        BinaryExpression("^", left, right) {}

    // the implementation of operation - Pow.
    double operation(double var1, double var2) {return pow(var1, var2);};
};


#endif //PROG1PROJECT_Mul_H
