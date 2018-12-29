//
// created by omri & gal on 12/17/18.
//

#include "ConditionParser.h"
#include "../Interpreter.h"
#include "../Utils.h"
#include "../Databases/SymbolsDB.h"
#include <algorithm>

Expression *ConditionParser::getCondition() {
    return _condition;
}

Interpreter *ConditionParser::getStatementsInterpreter() {
    Interpreter* i = _statesmentsInterpreter;
    i->reset();
    return i;
}

void ConditionParser::saveLastScopeSymbols() {
    _beforeScope = SymbolsDB::getSymbolsNames();
}

void ConditionParser::restoreLastScopeSymbols() {

    vector<string> afterScope = SymbolsDB::getSymbolsNames();

    // for each symbol name defined in the scope, that is in after scope but not in before scope, delete it.
    for(string& symbolName:afterScope) {

        // if we didn't find the symbolName in the symbols before the scope, it created on the
        // scope, and we delete it from the symbol table.
        if (find(_beforeScope.cbegin(), _beforeScope.cend(), symbolName) == _beforeScope.cend()) {
            SymbolsDB::removeSymbol(symbolName);
        }
    }
}

void ConditionParser::doCommand() {

    int i = 0;

    vector<string> conditionVec;

    // lex the condition part;

    while(args[i] != "{") {
        conditionVec.push_back(args[i]);
        i++;
    }

    // if no condtion lexed, than exception.
    if (conditionVec.size() == 0)
        throw ConditionalException("Conditional has no condition declared");

    // moving i to skip {.
    i++;

    // Interpreter the shunting yard of expression into the condition, so we can caluclate it next.
    _condition = Interpreter::shuntingYard(conditionVec);


    vector<string> statesments;
    // getts the inside of the { } brackets so we can execute them.
    for(i; i < args.size(); i++)
        statesments.push_back(args[i]);

    _statesmentsInterpreter = new Interpreter(statesments);

}

bool ConditionParser::anotherArg(string &current) {

    // stop when a } sign show, and the balance of { and } are 0.

    static int balance = 0;

    // if the current token is {, we raise the balance by 1, becuase another } will come before ours.

    if(current == "{")
        balance++;

    // if the current token is }, we take the balance off by 1, because a matching { was there before.
    if(current == "}") {
        balance--;

        // if the } is here, and a balance of } achieved, then we can stop reading characters.
        if(balance == 0)
            return false; // wait another 1 token - }, before stop excepting arguments.

        if (balance < 0)
            throw BracketsException("an unappropriate } was defined, without suited {");
    }

    // continue reading if it was not } with balance of 0.
    return true;
}

bool ConditionParser::goBackArg(string &current) {

    // condition parser dont need to read things before the keyword.
    return false;
}
