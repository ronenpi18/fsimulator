/*
     created by omri & gal and Gal on 12/9/18.
*/

#include "Interpreter.h"
#include "Databases/ConstsDB.h"
#include <stack>
#include <algorithm>
//#include <bits/refwrap.h>
#include "Databases/SymbolsDB.h"
#include "Expressions/ExpressionFactory.h"
#include "Utils.h"
#include "Expressions/Var.h"
#include "Exceptions.h"

/**
 * Shuting yard algortim -
 * get string @expression and return combined work of two functions
 * 1st - turns the infix expression to prefix expression as a vector of tokens (operators and numbers),
 * 2nd- turns the vector into an Expression object.
 *
 * */
Expression* Interpreter::shuntingYard(vector<string>& tokens) {

    vector<string> postfixVector = shuntingYard_infixToPostfix(tokens);

    // use 2nd function on the result of the 1st.
    return shuntingYard_postfixToExpression(postfixVector);

}

/**
 * shunting yard algorithm - the string to vector of tokens (operators and numbers) part -
 * converts mathematical expression specified in infix notation, into prefix
 * [ for example - 3 * 4 + 5 ---> +(5, *(3, 4))]
 */
vector<string> Interpreter::shuntingYard_infixToPostfix(vector<string>& tokens) {

    string prefix;
    vector<string> outputQueue;
    stack<string> operatorsStack;

    // while there is a token to read:
    std::map<string, int> op_precedence (ExpressionFactory::getOperatorsPrecedence());




    for(string& token: tokens) {

        if (ExpressionFactory::isUnaryOperator(token)) {
            operatorsStack.push(token);
        }
        else if(token == "(")
            operatorsStack.push(token);
        else if(token == ")") {
            while (!operatorsStack.empty() && operatorsStack.top() != "(") {
                outputQueue.push_back(operatorsStack.top());
                operatorsStack.pop();
                //cout << "Pop stack to output " << token << endl;
            }
            if (operatorsStack.size() != 0)
                operatorsStack.pop();
            //cout << "Pop stack " << token << endl;

        } else if (ExpressionFactory::isBinaryOperator(token)){
            while(!operatorsStack.empty() && operatorsStack.top() != "(" && ((op_precedence.at(operatorsStack.top()) > op_precedence.at(token))
                    || (op_precedence.at(operatorsStack.top()) == op_precedence.at(token) && ExpressionFactory::isLeftAccociative(token)))) {
                //cout << "Pop stack to output " << token << endl;
                outputQueue.push_back(operatorsStack.top());
                operatorsStack.pop();
            }
            operatorsStack.push(token);
            //cout << "Push " << token << " to stack" << endl;
        }
        // if its a number or variable name or whatever else.
        else {
            outputQueue.push_back(token);
        }
    }
    while (!operatorsStack.empty()){
        outputQueue.push_back(operatorsStack.top());

        //cout << "Pop stack to output " << operatorsStack.top() << endl;

        operatorsStack.pop();

    }

    return outputQueue;

}

/*
 * Shunting yard algorithm second part - of our own -
 * turns the vector of tokens exp, and turn it into Expression object.
 * */
Expression* Interpreter::shuntingYard_postfixToExpression(vector<string>& exp) {

    int n = exp.size();

    /*
     * else, we can know that the last token in exp is an operator token, so as for what it is
     * we can make the expression, where the right value of it will be starting from exp sub string of
     * n -1, and the left will be at teh sub string of k , where k is the place right expression end at.
     */

    string token = exp[n-1];
    if(!ExpressionFactory::isNaryOperator(token)) {

        // if the last token was not an operator,  then we want to just create a Number/varialbe out of it.
        exp.pop_back();
        double number;
        if (ExpressionFactory::isNumber(token)) {
          return new Number(Utils::to_number(token)); // cast from string of number , to int of the number.
        }
        // else, it is a variable, so we want to return it.
        else {

            // ddddd
            if (ConstsDB::containsCommand(token)) {
                throw SymbolException("Variable with name of language keyword is not allowed");
            }
            // if the variable is a keyword like TRUE, FALSE, we will give it a keyword value by the map.
            if (ConstsDB::containsKeyword(token)) {
                return new Number(ConstsDB::getKeywordValue(token));
            }
            if (!SymbolsDB::containsSymbol(token)) {
                //TODO
                if (SymbolsDB::isSourceSymbol(token))
                    return new Var(token);

                throw SymbolException("no symbol named " + token + " is defined.");
            } else {
                    return new Var(token);
            }
        }

    } else {

        // if last token is operator, as said, we can remove it, and preform the function at the refrenced exp,
        // acutally modifing it, then get the right and left expressions.

        exp.pop_back();
        vector<Expression*> subExpressions;

        for (int i  = 0; i < ExpressionFactory::howManySubExpressions(token); i++) {
            subExpressions.insert(subExpressions.begin(), shuntingYard_postfixToExpression(exp));
        }

        //create the result from the factory.

        Expression* result = ExpressionFactory::create(token, subExpressions);
        return result;

    }


}

void addTokenIfStartedNew(vector<string>& tokens, string& check1) {
    if(check1 != "") {
        tokens.push_back(check1);
        check1 = "";
    }
}

void addTokenIfStartedNew(vector<string>& tokens, char c) {
    if(c != 0) {
        string p = "";
        p += c;
        tokens.push_back(p);
    }
}

bool isLetterOrUnderscore(char c) {
    return    (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_');
}
void Interpreter::lexer(string& line) {
    /*
     *
     * The lexer should read the source code character by character, and send tokens to the parser.

        After each token, it should use the next character cto decide what kind of token to read.

        if c is a digit, collect an integer as long as you read digits
        if c is a letter, collect an identifier as long as you read identifier characters (digit, letter, ')
        if c is a double quote, collect a string literal as long as you read characters other than a double quote
        if c is space character (i.e. space, newline, or tab), ignore it and read next character
     * */

    vector<string> tokens;

    string tmpNumber = "";
    string tmpOperator = "";
    string tmpVariable = "";
    string tmpString = "";
    bool stringFollow = false;

    int i = 0;
    while(i < line.length())
    {
        char c = line[i];

        // if we following a string in qoutes, anything gets in the string.
        if (stringFollow) {

            // if we get a closing ", then save the string.
            if (c == '"') {
                tokens.push_back('"' + tmpString + '"');
                stringFollow = false;
            }

                // else recieve the char into the string.
            else
                tmpString += c;

        }

        // if not, seperate by char:
        else {


            // if the char is space
            if (c == ' ')  {

                // if what came before space was variable (not command) or number, we can have a place to put comma: check.
                if (tmpNumber!= "" || (tmpVariable != "" && !ConstsDB::containsCommand(tmpVariable))) {

                    // we go forward to the next letter that is not space:
                    while (line[i] == ' ') {
                        i++;
                    }
                    c = line[i];

                    // if the first char after the spaces is alpha/underscore or a digit or a parantheses
                    // it is an operator decription character, than we flush and push a comma to the tokens.
                    if (isLetterOrUnderscore(c) || isdigit(c) || c == ',' || c == '(' || c== ')') {
                        addTokenIfStartedNew(tokens, tmpNumber);
                        addTokenIfStartedNew(tokens, tmpVariable);

                        // force add token comma, if not exsists already.
                        if (c != ',')
                            addTokenIfStartedNew(tokens, ',');

                    }

                    // if it is an opertor descripted character, do nothing.

                    // continue to next round on last c.
                    continue;
                }



                addTokenIfStartedNew(tokens, tmpNumber);
                addTokenIfStartedNew(tokens, tmpVariable);
                addTokenIfStartedNew(tokens, tmpOperator);
            }

                // if the char is a digit or floating point, we will add it to the tmp number, that gains near digits.
            else if (isdigit(c) || c == '.') {

                //if an operaqtor came before digit, we will push it to tokens.
                addTokenIfStartedNew(tokens, tmpOperator);

                // but if it was letter before digits, its fine because we can have variables with
                //  both letters and digits. else it is a number.
                if (tmpVariable != "") {
                    tmpVariable += c;
                }
                else {
                    tmpNumber += c;
                }
                // if it is a letter or an underscore:
            } else if (isLetterOrUnderscore(c)) {

                addTokenIfStartedNew(tokens, tmpNumber);
                addTokenIfStartedNew(tokens, tmpOperator);
                tmpVariable += c;
            }
                // if it is a quotes mark, we start writing into a string and save the others.
            else if (c == '"') {
                addTokenIfStartedNew(tokens, tmpNumber);
                addTokenIfStartedNew(tokens, tmpOperator);
                stringFollow = true;
            }

                // else, it is an operator or brackets, so we will add the last tmp number created, if it is not empty,
                // and reset it, and add the the operator to the tokens.
            else {

                // checking if a - is for unary or binary minus. special case :
                if (c == '-') {

                    // if the minus sign came after a number/variable or parantheses, it must be binary.

                    if (tmpNumber != "" || tmpVariable != "" || tokens[tokens.size() - 1] == ")") {

                        // we insert the binary form of minus, -.
                        addTokenIfStartedNew(tokens, tmpNumber);
                        addTokenIfStartedNew(tokens, tmpVariable);
                        addTokenIfStartedNew(tokens, '-');
                    }


                    // else the minus sign came after an operator or function, or nothing, it must be unary.
                    else {
                        // save the operator till fur.
                        addTokenIfStartedNew(tokens, tmpOperator);

                        // we insert the unary form of minus, #.
                        tmpOperator += '#';

                    }

                // else, just add to operator.
                }

                // handle commas:
                else if (c == ',') {

                    // if a comma it shown, we flush all symbols to tokens (whihc of them that exsists)
                    addTokenIfStartedNew(tokens, tmpNumber);
                    addTokenIfStartedNew(tokens, tmpOperator);
                    addTokenIfStartedNew(tokens, tmpVariable);

                    // summit the comma
                    addTokenIfStartedNew(tokens, c);
                }

                // brackets:
                else if(c == '(' || c== ')') {
                    addTokenIfStartedNew(tokens, tmpNumber);
                    addTokenIfStartedNew(tokens, tmpOperator);
                    addTokenIfStartedNew(tokens, tmpVariable);

                    // add the parantheses.
                    addTokenIfStartedNew(tokens, c);
                }


                else {
                    tmpOperator += c;

                }

                // save the variable or number till fur.
                addTokenIfStartedNew(tokens, tmpNumber);
                addTokenIfStartedNew(tokens, tmpVariable);

            }
        }

       // promote i by 1 at line.
       i++;
    }

    // adds the variables that gained after the loop if not added before.
    addTokenIfStartedNew(tokens, tmpNumber);
    addTokenIfStartedNew(tokens, tmpOperator);
    addTokenIfStartedNew(tokens, tmpVariable);
    tokens.push_back(ConstsDB::ENDLINE_KEYWORD);

    // saves the lexed tokens into current args of interpreter.
    _tokens = tokens;
}


void Interpreter::parser() {

    // reset tokens index to 0
    _index = 0;

    // if we don't need more lines, mean we staring new command, than we make the needed premake:
    // generate a command from keyword, and gain prev keyword args.

    while (_index < _tokens.size()) {
        if (!_isNeededMoreLines) {

            // intilizing args to empty vector.
            _currentArgs = vector<string>();

            // gain vars until a keyword.
            while (_index < _tokens.size() && !ConstsDB::containsCommand(_tokens[_index])) {
                _index++;
            }

            // creates a command by the command keyword.
            _currentCommand = ConstsDB::createCommand(_tokens[_index], _currentArgs);

            // skip the keyword:
            _index++;

            // substruct _index backwards while the command ask for go back
            while (_index > 0 && _currentCommand->goBackArg(_tokens[_index])) {
                _index--;
            }


        }
        else {
            cout << endl;
        }

        // now we want to read until end of the command args:

        bool hungry = false;
        while (_index < _tokens.size() && (hungry = _currentCommand->anotherArg(_tokens[_index]))) {

            _currentArgs.push_back(_tokens[_index]);
            _index++;
        }

        // if we stop reading because we reached the end of the given input, but the command was hungry for more,
        // we will stop funtion and continue in next call of parse, on the next line.
        if (_index == _tokens.size() && hungry) {
            _isNeededMoreLines = true;
            return;
        }
            // else, we read all line, and we can do the command:

        else {

            // command object do the command on the arguments list.
            _currentCommand->doCommand();
            // adding the command to the stack of commands;
            _commandsStack.push_back(_currentCommand);

            _currentCommand = nullptr;

            // setting that the command arguments is over.
            _isNeededMoreLines = false;
        }
    }
}

Interpreter::~Interpreter() {
    delete _currentCommand;
    for(Command* c:_commandsStack) {
        delete c;
    }

}

void Interpreter::reset() {
    _index = 0;
    _isNeededMoreLines = false;
    _currentCommand = nullptr;
}
