//
// created by omri & gal on 12/22/18.
//

#ifndef PROG1PROJECT_SYMBOL_H
#define PROG1PROJECT_SYMBOL_H

#include <string>

/**
 * interface Symbol represent a symbol with name, value and setters and getter to the value.000
 */
class Symbol {
public:
    virtual std::string getName() = 0;
    virtual double getValue() = 0;
    virtual void setValue(double newVal) = 0;

};

#endif //PROG1PROJECT_SYMBOL_H
