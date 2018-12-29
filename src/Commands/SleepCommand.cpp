//
// created by omri & gal on 12/24/18.
//

#include <unistd.h>
#include <thread>
#include <chrono>
#include "SleepCommand.h"
#include "../Databases/ConstsDB.h"
#include "../Utils.h"

void SleepCommand::doCommand() {

    unsigned int msToSleep = (int) Utils::SplitCommaArgsToExpressions(args)[0]->calculate();

    // makes the thread sleep.
    std::this_thread::sleep_for(std::chrono::milliseconds(msToSleep));

}

bool SleepCommand::anotherArg(string &current) {
    return current!=ConstsDB::ENDLINE_KEYWORD;
}

bool SleepCommand::goBackArg(string &current) {
    return false;
}
