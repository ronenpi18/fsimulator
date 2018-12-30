//
// created by Chenon 12/18/18.
//

#include "Consts.h"
#include "../Commands/Creators.h"
//intilizing const maps:

const string Consts::ENDLINE_KEYWORD = ";";

// inner use to intilize maps:

map<string, CommandCreator*> Consts::createCommandsByNames() {

map<string, CommandCreator*> m =
        {{ "if", new IfCommandCreator() }, { "while", new WhileCommandCreator() },
         { "openDataServer", new OpenDataServerCommandCreator() }, { "print", new PrintCommandCreator()} ,
         {Consts::ENDLINE_KEYWORD, new SemicolonCommandCreator()}, {"=", new EqualsCommandCreator()},
         {"var", new DefineVarCommandCreator()}, {"connect", new ConnectCommandCreator()}, {"sleep", new SleepCommandCreator()}
         , {"bind", new SemicolonCommandCreator()}, {"enterc", new EnterCCommandCreator()}
        };

    return m;
};

// now create the maps:
map<string, CommandCreator*> Consts::_commandsByNames = Consts::createCommandsByNames();

map<string, double> Consts::_keywordValues = Consts::createKeywordValues();

map<string, double> Consts::createKeywordValues() {
    map<string, double> m = {{ "true", 1 }, { "false", 0 }};
    return m;
};

Command* Consts::createCommand(string name, vector<string>& args) {
    if(_commandsByNames.count(name) != 0) {
        // TODO: CHANGE TO FACTORY.
        return _commandsByNames.at(name)->create(args);
    }
    else {
        throw CommandException("Command (keyword) name is not defined");
    }

}

CommandCreator *Consts::getCommand(string name) {
    if(_commandsByNames.count(name) != 0) {
        return  _commandsByNames.at(name);
    }
    else {
        throw CommandException("Command (keyword) name is not defined");
    }
}

double Consts::getKeywordValue(string name) {
    if(_keywordValues.count(name) != 0) {
        return  _keywordValues.at(name);
    }
    else {
        throw KeywordException("Keyword is not defined");
    }
}
bool Consts::containsKeyword(string name) {
    return _keywordValues.count(name) != 0;
}

bool Consts::containsCommand(string name) {
    return _commandsByNames.count(name) != 0;
}

void Consts::destroyAllDB() {
    for(map<string, CommandCreator*>::iterator p = _commandsByNames.begin(); p != _commandsByNames.end(); ++p) {
        if(p->second != nullptr)
            delete p->second;

    }
}
