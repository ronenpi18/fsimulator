//
// created by omri & gal on 12/24/18.
//

#ifndef PROG1PROJECT_CREATORS_H
#define PROG1PROJECT_CREATORS_H

// here is all creators of commands:


#include "CommandCreator.h"
#include "OpenDataServerCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"
#include "ConnectCommand.h"
#include "SemicolonCommand.h"
#include "PrintCommand.h"
#include "EqualsCommand.h"
#include "DefineVarCommand.h"
#include "SleepCommand.h"
#include "EnterCCommand.h"

class OpenDataServerCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new OpenDataServerCommand(CommandArgs);
    }
};

class IfCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new IfCommand(CommandArgs);
    }
};

class WhileCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new WhileCommand(CommandArgs);
    }
};

class ConnectCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new ConnectCommand(CommandArgs);
    }
};

class SemicolonCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new SemicolonCommand(CommandArgs);
    }
};

class PrintCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new PrintCommand(CommandArgs);
    }
};

class EqualsCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new EqualsCommand(CommandArgs);
    }
};

class DefineVarCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new DefineVarCommand(CommandArgs);
    }
};

class SleepCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new SleepCommand(CommandArgs);
    }
};

class EnterCCommandCreator : public CommandCreator{
    Command *create(vector<string>& CommandArgs) override {
        return new EnterCCommand(CommandArgs);
    }
};

#endif //PROG1PROJECT_CREATORS_H
