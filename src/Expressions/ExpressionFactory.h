//
// created by omri & gal on 12/12/18.
//

#ifndef PROG1PROJECT_EXPRESSIONFACTORY_H
#define PROG1PROJECT_EXPRESSIONFACTORY_H

#include "../Expression.h"
#include <map>
#include <string>
#include <vector>

using namespace std;
class ExpressionFactory {

private:
    static map<string, int> createMap1();
    static map<string, int> createMap2();
    static map<string, int> createNarity();

    static map<string, int> operatorsPrecedence;
    static map<string, int> functionsPrecedence;
    static map<string, int> nArity;     // maps between operator symbol and how many sub expressions it has.

public:

    // getter for operatorsPrecedence
    static map<string, int> getOperatorsPrecedence();

    // create functions, which create expression by the token representing them.
    //Expression* create(char function, Expression* exp);
    static Expression* create(string operatora, vector<Expression*> subExpressions);

    static int howManySubExpressions(string token);

    // helping function to determine if a string represent one of our operators.
    static bool isBinaryOperator(string token);

    // helping function to determine if a string represent one of our functions - unary operator.
    static bool isUnaryOperator(string token);

    static bool isNaryOperator(string token);

    // helping function to determine if a string represent number.
    static bool isNumber(string token);

    // helping function to determine if a char represent one of our operators, that is left associative,
    // means that a~b~c = (a~b)~c.
    static bool isLeftAccociative(string operat);


};


#endif //PROG1PROJECT_EXPRESSIONFACTORY_H
