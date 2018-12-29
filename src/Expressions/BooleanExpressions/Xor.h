//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_XOR_H
#define PROG1PROJECT_XOR_H


#include "../BinaryExpression.h"

class Xor : public BinaryExpression {

public:

    // constructor.
    Xor(Expression* left, Expression* right):
        BinaryExpression("^^", left, right) {}

    // the implementation of operation - Xor.
    double operation(double var1, double var2) {return (var1 != 0) ^ (var2 != 0);};
};


#endif //PROG1PROJECT_XOR_H
