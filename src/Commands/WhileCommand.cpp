//
// created by omri & gal on 12/17/18.
//

#include "WhileCommand.h"

void WhileCommand::doCommand() {

    saveLastScopeSymbols();

    // do parent condition parser to get the condition and statements.
    ConditionParser::doCommand();

    while(getCondition()->calculate() > 0) {
        getStatementsInterpreter()->parser();

    }
    restoreLastScopeSymbols();

}
