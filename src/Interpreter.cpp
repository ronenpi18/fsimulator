/*
     created by Chen
*/

#include "Interpreter.h"
#include "Databases/Consts.h"
#include <stack>
#include <algorithm>
#include "Databases/SymbolsDB.h"
#include "Expressions/ExpressionFactory.h"
#include "Common/Utils.h"
#include "Expressions/Var.h"
#include "Common/Exceptions.h"


/*
 * shuntingYard function
 * params - an array of words
 */
Expression* Interpreter::shuntingYard(vector<string>& words) {
    vector<string> postfixVector = shuntingYard_infixToPostfix(words);
    // use 2nd function on the result of the 1st.
    return shuntingYard_postfixToExpression(postfixVector);
}

/*
 * shuntingYard_infixToPostfix function
 * params - an infix Expressions
 */
vector<string> Interpreter::shuntingYard_infixToPostfix(vector<string>& infixExpression) {
    string prefix;
    vector<string> outputQueue;
    stack<string> operatorsStack;
    std::map<string, int> operatorPrecedence (ExpressionFactory::getOperatorsPrecedence());
    // while there is a word to read
    for(string& word: infixExpression) {
        if (ExpressionFactory::isUnaryOperator(word)) {
            operatorsStack.push(word);
        }
        else if(word == "(")
            operatorsStack.push(word);
        else if(word == ")") {
            while (!operatorsStack.empty() && operatorsStack.top() != "(") {
                outputQueue.push_back(operatorsStack.top());
                operatorsStack.pop();
            }
            if (operatorsStack.size() != 0)
                operatorsStack.pop();
        } else if (ExpressionFactory::isBinaryOperator(word)){
            while(!operatorsStack.empty() && operatorsStack.top() != "(" && ((operatorPrecedence.at(operatorsStack.top()) > operatorPrecedence.at(word))
                    || (operatorPrecedence.at(operatorsStack.top()) == operatorPrecedence.at(word) && ExpressionFactory::isLeftAccociative(word)))) {
                outputQueue.push_back(operatorsStack.top());
                operatorsStack.pop();
            }
            operatorsStack.push(word);
        }
        else {
            outputQueue.push_back(word);
        }
    }
    while (!operatorsStack.empty()){
        outputQueue.push_back(operatorsStack.top());
        operatorsStack.pop();
    }
    return outputQueue;
}

/*
 * shuntingYard_postfixToExpression function
 * params - postfixExpression
 * Shunting yard algorithm second part - of our own -
 * turns the vector of tokens exp, and turn it into Expression object.
 * */
Expression* Interpreter::shuntingYard_postfixToExpression(vector<string>& postfixExpression) {
    int n = postfixExpression.size();
    /*
     * else, we can know that the last token in exp is an operator token, so as for what it is
     * we can make the expression, where the right value of it will be starting from exp sub string of
     * n -1, and the left will be at teh sub string of k , where k is the place right expression end at.
     */
    string word = postfixExpression[n-1];
    if(!ExpressionFactory::isNaryOperator(word)) {

        // if the last token was not an operator,  then we want to just create a Number/varialbe out of it.
        postfixExpression.pop_back();
        double number;
        if (ExpressionFactory::isNumber(word)) {
          return new Number(Utils::to_number(word)); // cast from string of number , to int of the number.
        }
        // else, it is a variable, so we want to return it.
        else {

            // ddddd
            if (Consts::containsCommand(word)) {
                throw SymbolException("Variable with name of language keyword is not allowed");
            }
            // if the variable is a keyword like TRUE, FALSE, we will give it a keyword value by the map.
            if (Consts::containsKeyword(word)) {
                return new Number(Consts::getKeywordValue(word));
            }
            if (!SymbolsDB::containsSymbol(word)) {
                if (SymbolsDB::isSourceSymbol(word))
                    return new Var(word);
                throw SymbolException("no symbol named " + word + " is defined.");
            } else {
                    return new Var(word);
            }
        }

    } else {

        // if last token is operator, as said, we can remove it, and preform the function at the refrenced exp,
        // acutally modifing it, then get the right and left expressions.

        postfixExpression.pop_back();
        vector<Expression*> subExpressions;

        for (int i  = 0; i < ExpressionFactory::howManySubExpressions(word); i++) {
            subExpressions.insert(subExpressions.begin(), shuntingYard_postfixToExpression(postfixExpression));
        }

        //create the result from the factory.

        Expression* result = ExpressionFactory::create(word, subExpressions);
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
                if (tmpNumber!= "" || (tmpVariable != "" && !Consts::containsCommand(tmpVariable))) {

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
    tokens.push_back(Consts::ENDLINE_KEYWORD);

    // saves the lexed tokens into current args of interpreter.
    words = tokens;
}


void Interpreter::parser() {

    // reset tokens index to 0
    myIndex = 0;

    // if we don't need more lines, mean we staring new command, than we make the needed premake:
    // generate a command from keyword, and gain prev keyword args.

    while (myIndex < words.size()) {
        if (!nextLineNeeded) {

            // intilizing args to empty vector.
            currentArgs = vector<string>();

            // gain vars until a keyword.
            while (myIndex < words.size() && !Consts::containsCommand(words[myIndex])) {
                myIndex++;
            }

            // creates a command by the command keyword.
            currentCommand = Consts::createCommand(words[myIndex], currentArgs);

            // skip the keyword:
            myIndex++;

            // substruct _index backwards while the command ask for go back
            while (myIndex > 0 && currentCommand->goBackArg(words[myIndex])) {
                myIndex--;
            }


        }
        else {
            cout << endl;
        }

        // now we want to read until end of the command args:

        bool hungry = false;
        while (myIndex < words.size() && (hungry = currentCommand->anotherArg(words[myIndex]))) {

            currentArgs.push_back(words[myIndex]);
            myIndex++;
        }

        // if we stop reading because we reached the end of the given input, but the command was hungry for more,
        // we will stop funtion and continue in next call of parse, on the next line.
        if (myIndex == words.size() && hungry) {
            nextLineNeeded = true;
            return;
        }
            // else, we read all line, and we can do the command:

        else {

            // command object do the command on the arguments list.
            currentCommand->doCommand();
            // adding the command to the stack of commands;
            commandsStack.push_back(currentCommand);

            currentCommand = nullptr;

            // setting that the command arguments is over.
            nextLineNeeded = false;
        }
    }
}

Interpreter::~Interpreter() {
    delete currentCommand;
    for(Command* c:commandsStack) {
        delete c;
    }

}

void Interpreter::reset() {
    myIndex = 0;
    nextLineNeeded = false;
    currentCommand = nullptr;
}
