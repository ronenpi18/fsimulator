//
// created by omri & gal on 12/24/18.
//

#ifndef PROG1PROJECT_COMMANDCREATOR_H
#define PROG1PROJECT_COMMANDCREATOR_H

#include "../Command.h"

// commandCrator is an interface creating command of the implementator, with command args as input.


class CommandCreator {
public:
    virtual Command* create(vector<string>& CommandArgs) = 0;
};
#endif //PROG1PROJECT_COMMANDCREATOR_H
