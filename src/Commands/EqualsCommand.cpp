//
// created by omri & gal on 12/18/18.
//

#include "EqualsCommand.h"
#include "../Utils.h"
#include "../Databases/ConstsDB.h"
#include "../Databases/SymbolsDB.h"
#include "../Interpreter.h"

void EqualsCommand::doCommand() {
    // TODO: handle bind.
    // arguments are: varName, = , (optional bind) ..... (expression).

    string varName = args[0];

    // if varName = bind (expression), request to bind between them:
    if (args.size() > 2 && args[2] == "bind") {

        // binds between first and second var.
        string& otherArgName = args[3];
        SymbolsDB::bind(varName, otherArgName);
        SymbolsDB::setSymbol(varName, SymbolsDB::getSymbol(otherArgName));

    }
    else {

        vector<string> expressionArgs(args.begin() + 2, args.end());

        // creates an expression with shunting yard.
        Expression *e = Interpreter::shuntingYard(expressionArgs);


        // assign value of expression to varName;
        SymbolsDB::setSymbol(varName, e->calculate());

        // deleting memory of e.
        delete e;
    }

}

bool EqualsCommand::anotherArg(string &current) {
    // get the whole line.
    return !(current == ConstsDB::ENDLINE_KEYWORD);
}

bool EqualsCommand::goBackArg(string &current) {

    // go back 1, to a var name to assigned to. and another behind the = sign.
    return Utils::getNArguments(_internalUseN);
}
