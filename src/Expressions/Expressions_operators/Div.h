//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_Div_H
#define PROG1PROJECT_Div_H


#include "../BinaryExpression.h"
#include "../../Exceptions.h"

class Div : public BinaryExpression {

public:

    // constructor.
    Div(Expression* left, Expression* right):
        BinaryExpression("/", left, right) {}

    // the implementation of operation - Div.
    double operation(double var1, double var2) {
        if (var2 == 0) {throw DevisionByZeroException("can't devide by 0");}
        return var1 / var2;
    };
};


#endif //PROG1PROJECT_Div_H
