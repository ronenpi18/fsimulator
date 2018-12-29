//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_NUMBER_H
#define PROG1PROJECT_NUMBER_H

#include "../Expression.h"
#include <iostream>
#include <cmath>
class Number : public Expression {
private:

    double _value;
public:
    // constructor:
    explicit Number(double num) :
            _value(num) {};

    // getter for number:
    double getNumber() const { return _value; };

    // getter of num.
    double calculate() { return _value; };

    //output operator:
    friend std::ostream &operator<<(std::ostream &output, const Number &number) {
        output << number.toString();
        return output;
    }

    std::string toString() const {

        // if the value is an integer, print it like integer.

        if (std::floor(_value) == _value) {
            return std::to_string((int) _value);
        }

        // else, if it is pure double:
        return std::to_string(_value);
    }

    ~Number() {}
};
#endif //PROG1PROJECT_NUMBER_H
