//
// created by omri & gal on 12/10/18.
//

#ifndef PROG1PROJECT_Var_H
#define PROG1PROJECT_Var_H

#include "../Expression.h"
#include <iostream>
#include <cmath>
#include "../Databases/SymbolsDB.h"

class Var : public Expression{
private:

   std::string _varName;
public:
    // constructor:
    explicit Var(std::string varName):
        _varName(varName) {};

    // getter for Var:
    std::string getVar() const {return _varName;};

    // getter of num.
    double calculate() { return SymbolsDB::getSymbol(_varName); };

    //output operator:
    friend std::ostream& operator<<(std::ostream& output, const Var& Var) {
        output << Var.toString();
        return output;
    }
    std::string toString() const {return _varName; }

    ~Var() {};

};
//g++ Databases/*.h Databases/*.cpp Expressions/*.h Expressions/*.cpp Commands/*.h Commands/*.cpp  main.cpp Command.h Expression.h Expressions.h Interpreter.h Interpreter.cpp Utils.h Utils.cpp -std=c++1y
#endif //PROG1PROJECT_Var_H
