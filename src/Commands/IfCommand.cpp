//
// created by omri & gal on 12/17/18.
//

#include "IfCommand.h"

void IfCommand::doCommand() {

    saveLastScopeSymbols();
    // do parent condition parser to get the condition and statements.
    ConditionParser::doCommand();

    if(getCondition()->calculate() > 0) {
        getStatementsInterpreter()->parser();

    }
    restoreLastScopeSymbols();

}
