//
// created by omri & gal on 12/17/18.
//

#ifndef PROG1PROJECT_CONDITIONPARSER_H
#define PROG1PROJECT_CONDITIONPARSER_H

#include "../Command.h"
#include "../Expressions.h"
#include "../Interpreter.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

class ConditionParser : public Command{

private:

    // condition expression.
    Expression* _condition;

    // script of statements to execute:
    Interpreter* _statesmentsInterpreter;

    // vector of symbol names before entered the scope.
    vector<string> _beforeScope;
protected:

    vector<string>& args;
    //getters:

    Expression* getCondition();
    Interpreter* getStatementsInterpreter();

    // save the current symbol table var names into our list.
    void saveLastScopeSymbols();

    // restore the symbols defined in symbol table before the scope.
    void restoreLastScopeSymbols();


public:
    ConditionParser(vector<string>& v):
        args(v) {};
    void doCommand() override;

    bool anotherArg(string &current)override;

    bool goBackArg(string &current) override;


};


#endif //PROG1PROJECT_CONDITIONPARSER_H
