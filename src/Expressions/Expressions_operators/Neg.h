//
// created by omri & gal on 12/21/18.
//

#ifndef PROG1PROJECT_NEG_H
#define PROG1PROJECT_NEG_H

#include "../UnaryExpression.h"

class Neg: public UnaryExpression {
public:

    // constructor:
    Neg(Expression* ex):
        UnaryExpression("#", ex) {};

    // operation:
    double operation(double val) override {
        return (-1)*val;
    }
};
#endif //PROG1PROJECT_NEG_H
