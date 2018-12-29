//
// created by omri & gal on 12/12/18.
//"

#include "ExpressionFactory.h"
#include "Expressions_operators/Div.h"
#include "Expressions_operators/Plus.h"
#include "Expressions_operators/Minus.h"
#include "Expressions_operators/Mul.h"
#include "Expressions_operators/Pow.h"
#include "BooleanExpressions/Bigger.h"
#include "BooleanExpressions/Smaller.h"
#include "BooleanExpressions/Equals.h"
#include "BooleanExpressions/NotEquals.h"
#include "BooleanExpressions/Xor.h"
#include "BooleanExpressions/Or.h"
#include "BooleanExpressions/And.h"
#include "BooleanExpressions/BiggerEquals.h"
#include "BooleanExpressions/SmallerEquals.h"
#include "Expressions_operators/Neg.h"



// create expression by the token representing them.
Expression *ExpressionFactory::create(string operatora, vector<Expression*> subExpressions) {

    // binary expressions creation:
    if(subExpressions.size() == 2) {
        Expression* left = subExpressions[0];
        Expression* right = subExpressions[1];

        if (operatora == "+")
            return new Plus(left, right);
        if (operatora == "-")
            return new Minus(left, right);
        if (operatora == "*")
            return new Mul(left, right);
        if (operatora == "/")
            return new Div(left, right);
        if (operatora == "^")
            return new Pow(left, right);
        if (operatora == ">")
            return new Bigger(left, right);
        if (operatora == "<")
            return new Smaller(left, right);
        if (operatora == "==")
            return new Equals(left, right);
        if (operatora == "!=")
            return new NotEquals(left, right);
        if (operatora == ">=")
            return new BiggerEquals(left, right);
        if (operatora == "<=")
            return new SmallerEquals(left, right);
        if (operatora == "&&")
            return new And(left, right);
        if (operatora == "||")
            return new Or(left, right);
        if (operatora == "^^")
            return new Xor(left, right);
    }

    // unary expressions creation:
    else if (subExpressions.size() == 1) {

        Expression* sub = subExpressions[0];
        if (operatora == "#")
            return new Neg(sub);
    }


    // if the operator is unknown, return nullptr.
    return nullptr;
}

int ExpressionFactory::howManySubExpressions(string token) {
    if(nArity.count(token) == 0)
        return 0;
    else
        return nArity.at(token);
}

map<string, int> ExpressionFactory::createMap1() {
    map<string, int> m =
            {
                    {"+",  10},
                    {"-",  10},
                    {"*",  20},
                    {"/",  20},
                    {"^",  30},
                    {">",  1},
                    {"<",  1},
                    {"==", 1},
                    {"!=", 1},
                    {">=", 1},
                    {"<=", 1},
                    {"||", 0},
                    {"&&", 0},
                    {"^^", 0},
                    {"#", 100}

            };
    return m;
}
map<string, int> ExpressionFactory::createMap2() {
    map<string, int> m =
            {
                    {"#",  20}
            };
    return m;
}
map<string, int> ExpressionFactory::createNarity() {
    map<string, int> m =
            {
                    {"+",  2},
                    {"-",  2},
                    {"*",  2},
                    {"/",  2},
                    {"^",  2},
                    {">",  2},
                    {"<",  2},
                    {"==", 2},
                    {"!=", 2},
                    {">=", 2},
                    {"<=", 2},
                    {"||", 2},
                    {"&&", 2},
                    {"^^", 2},
                    {"#",  1},
            };
    return m;
}
map<string, int> ExpressionFactory::operatorsPrecedence = ExpressionFactory::createMap1();
map<string, int> ExpressionFactory::functionsPrecedence = ExpressionFactory::createMap2();
map<string, int> ExpressionFactory::nArity = ExpressionFactory::createNarity();


// helping function to determine if a string represent one of our operators.

bool ExpressionFactory::isBinaryOperator(string token) {
    return (ExpressionFactory::operatorsPrecedence.count(token) > 0);
}

bool ExpressionFactory::isUnaryOperator(string token) {
    return (ExpressionFactory::functionsPrecedence.count(token) > 0);
}

bool ExpressionFactory::isNaryOperator(string token) {
    return isUnaryOperator(token) || isBinaryOperator(token);
}

// helping function to determine if a string represent number.
bool ExpressionFactory::isNumber(string token) {

    // check out that the string is not empty.
    if(token == "")
        return false;

    // iterating over the string to see if there is a char that is not a digit:
    for(int i = 0; i < token.length(); i++) {
        char c = token[i];
        if (!(isdigit(c) || c == '.'))
            return false;
    }
    // if all chars are digits, its a number.
    return true;
}

// helping function to determine if a char represent one of our operators, that is left associative,
// means that a~b~c = (a~b)~c.
bool ExpressionFactory::isLeftAccociative(string operat) {
    if(operat == "/" )
        return true;
    else
        return false;
}

map<string, int> ExpressionFactory::getOperatorsPrecedence() {
    return ExpressionFactory::operatorsPrecedence;
}

