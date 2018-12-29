//
// created
//

#ifndef PROG1PROJECT_UTILS_H
#define PROG1PROJECT_UTILS_H

#include <string>
#include <vector>
#include "Expression.h"

using namespace std;

class Utils {
public:

    // cast string to int.
    static double to_number(string s);

    // returns true N times, than after that false.
    static bool getNArguments(int& N);

    // splits a string str by a token. returned in vector. if the token not found, str returned as
    // the only in the vector.
    template <class T>
    static vector<vector<T>> split(vector<T>, T token);

    // split the vector by commas (,) and create an expression from each part.
    static vector<Expression*> SplitCommaArgsToExpressions(vector<string> tokens);

    // split string using split.
    static vector<string> strSplit(string str, char token);


    };
/**
 * g++ Expressions/*.h Expressions/*.cpp DataBase.cpp DataBase.h Expression.h Expressions.h Utils.h Utils.cpp Expressions/BooleanExpressions/*.h Expressions/Expressions_operators/*.h

 */

#endif //PROG1PROJECT_UTILS_H
