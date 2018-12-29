//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_BINARYEXPRESSION_H
#define PROG1PROJECT_BINARYEXPRESSION_H

#include "../Expression.h"
#include <string>
#include <iostream>
/*
 * interface BinaryExpression, which is an Expression
 * has left and right expression, and
 * */
class BinaryExpression : public Expression {
private:

    std::string _sign;
    Expression* _left;
    Expression* _right;
public:

    // getter: returns left expression.
    Expression* getLeft() const{ return _left;} ;

    // getter: returns right expression.
    Expression* getRight()  const{return _right;};

    // getter: return the sign of the expression (std::string).
    std::string getSign() const{return _sign;} ;

    // (abstract) constructor.
    BinaryExpression(std::string sign, Expression* left, Expression* right):
            _sign(sign), _left(left), _right(right) {}

    // abstract method that the operation implements.
    virtual  double operation(double val1, double val2) = 0;

    double calculate() {
        return operation(_left->calculate(), _right->calculate());
    }
    // output operator:
    friend std::ostream &operator<<( std::ostream &output, const BinaryExpression& be) {
        output << be.toString();
        return  output;
    }
    std::string toString() const {return "(" + _left->toString() +  _sign + _right->toString() + ")";}

    // destructor:
    ~BinaryExpression() {
        delete _left;
        delete _right;
    }
};

#endif //PROG1PROJECT_BINARYEXPRESSION_H
