//
// created by omri & gal on 12/18/18.
//

#include "DefineVarCommand.h"
#include "../Utils.h"
#include "../Databases/SymbolsDB.cpp"
#include "../Databases/ConstsDB.cpp"

void DefineVarCommand::doCommand() {

    string varName = args[0];

    // if the variable name is not a command/keyword.
    if (ConstsDB::containsCommand(varName) || ConstsDB::containsKeyword(varName)) {
        throw SymbolException("Variable with name of language keyword is not allowed");
    }
    // check that var name is not define.
    if (SymbolsDB::containsSymbol(varName)) {
        throw SymbolException("Varialbe " + varName + " is already declared");
    }

    // defualt value of unintilize varialbe.
    SymbolsDB::addSymbol(varName);
}

bool DefineVarCommand::anotherArg(string &current) {

    return Utils::getNArguments(_internalUseN);

    // varCommand defined by: "var x"


}

bool DefineVarCommand::goBackArg(string &current) {
    // varCommand is not need anything before var.
    return false;
}
