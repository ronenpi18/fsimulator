//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_OR_H
#define PROG1PROJECT_OR_H


#include "../BinaryExpression.h"

class Or : public BinaryExpression {

public:

    // constructor.
    Or(Expression* left, Expression* right):
        BinaryExpression("||", left, right) {}

    // the implementation of operation - Or.
    double operation(double var1, double var2) {return var1 || var2;};
};


#endif //PROG1PROJECT_OR_H
