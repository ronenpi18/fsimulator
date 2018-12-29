

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
 *  class Interpreter:
 *  constits of few main functionalities:
 *  to lexe from file or command line into strings array
 *  to parse from the string array into the map of variables - commands.
 *  to
*/

class Interpreter {
private:

    Command* _currentCommand;
    vector<Command*> _commandsStack;
    vector<string> _tokens;
    vector<string> _currentArgs;
    int _index = 0;
    bool _isNeededMoreLines;

    // help functions:
    static vector<string> shuntingYard_infixToPostfix(vector<string>& infix_token);

    static  Expression* shuntingYard_postfixToExpression(vector<string>& exp);


    // filter string representing expression into vector of tokens - (numbers, operators and brackets).
    static vector<string> filterExpressionString(string expression);
public:


    // interpreter constructor, which builds around the code from lexed list, start with index = 0.
    Interpreter(vector<string> code):
        _currentCommand(nullptr), _index(0),  _tokens(code), _currentArgs(), _isNeededMoreLines(false) {};

    // interpreter constructor, which build new interpreter ready to lex and parse in this order.
    Interpreter():
        _currentCommand(nullptr), _index(0),  _tokens(), _currentArgs(), _isNeededMoreLines(false) {};


    // lexer - from file, gets the next line of command into string[].
    void lexer(string& line);

    // parser - from a commmandLine representing a command, parse it into command and do it.
    void parser();

    // ‫‪Shunting-yard‬‬ of Dikstra - parse a string into a Expression (only binaries expressions).
    static Expression* shuntingYard(vector<string>& tokens);

    // destructor which also deleting all commands and their important recouses.
    ~Interpreter();

    void reset();

};

#endif //PROG1PROJECT_Interpreter_H
