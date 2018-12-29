//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_UNARYEXPRESSION_H
#define PROG1PROJECT_UNARYEXPRESSION_H

#include "../Expression.h"
#include <string>
#include <iostream>
/*
 * interface UnaryExpression, which is an Expression of only one expression.
 * */
class UnaryExpression : public Expression {
private:
    Expression* _expression;
    std::string _sign;

public:
    // constructor:
    UnaryExpression(std::string sign, Expression* expression) :
        _sign(sign), _expression(expression)  {}

    // returns the expression..
    Expression* getExpression()  const{ return _expression; }
    std::string getSign() const{ return  _sign;}

    // abstract method that the operation implements.
    virtual  double operation(double val) = 0;

    double calculate() {
        return operation(_expression->calculate());
    }

    // output operator:
    friend std::ostream &operator<<( std::ostream &output, const UnaryExpression& ue) {
        output << ue.toString();
        return output;
    }

    std::string toString()  const {
        return _sign + _expression->toString();
    }
    ~UnaryExpression() {delete _expression;}
};
#endif //PROG1PROJECT_UNARYEXPRESSION_H
