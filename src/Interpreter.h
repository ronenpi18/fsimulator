

#ifndef PROG1PROJECT_Interpreter_H
#define PROG1PROJECT_Interpreter_H
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "Command.h"
#include "Expressions.h"
using namespace std;
/*
 *  class Interpreter
 *  gets a line of the code or an empty line in the code
 *  using the lexer in order to converts the line into array of strings
 *  using the parser in order to convrts the words from the string array into commands
*/

class Interpreter {
    // private members and functions
private:
    // private members
    Command* currentCommand;
    vector<Command*> commandsStack;
    vector<string> words;
    vector<string> currentArgs;
    int myIndex = 0;
    bool nextLineNeeded;

    // private functions
    static vector<string> shuntingYard_infixToPostfix(vector<string>& infixExpression);
    static Expression* shuntingYard_postfixToExpression(vector<string>& postfixExpression);

    // public functions
public:
    // interpreter constructor
    // params - an array of all the words in one line of the given code
    Interpreter(vector<string> line):
        currentCommand(nullptr), myIndex(0),  words(line), currentArgs(), nextLineNeeded(false) {};

    // interpreter constructor
    // no params given
    Interpreter():
        currentCommand(nullptr), myIndex(0),  words(), currentArgs(), nextLineNeeded(false) {};

    // lexer function
    // params - the next line
    // split the line into an array of strings
    void lexer(string& line);

    // parser function
    // params - no params given
    // connect all the words to commands according to the map and execute them
    void parser();

    // shuntingYard function
    // params - an array of all the words in the line
    // according to the shuntingYard algorithm, converts every word into a binary expression
    static Expression* shuntingYard(vector<string>& words);

    // reset function
    void reset();

    // interpreter destructor
    ~Interpreter();
};

#endif //PROG1PROJECT_Interpreter_H
