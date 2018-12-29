//
// created by omri & gal on 12/18/18.
//

#ifndef PROG1PROJECT_CONSTSDB_H
#define PROG1PROJECT_CONSTSDB_H

#include "../Expressions.h"
#include <string>
#include <map>
#include "../Command.h"
#include "../Commands/PrintCommand.h"
#include "../Commands/CommandCreator.h"

class ConstsDB {

private:

// initliztion of string names to command object map:
    static map<string, CommandCreator *> createCommandsByNames();

    // intiliztion of string names to keyword values map:

    static map<string, double> createKeywordValues();

    // keyword defualt variables name to value.
    static map<string, double> _keywordValues;

    // commands table - between name and command object.
    static map<string, CommandCreator*> _commandsByNames;

public:
    static const string ENDLINE_KEYWORD;

    static Command* createCommand(string name, vector<string>& args);
        // get a command object by name.
    static CommandCreator *getCommand(string name);

    static bool containsCommand(string name);

    // get a keyword value by name.
    static double getKeywordValue(string name);

    // destrucor:
    static void destroyAllDB();

    // check if a keyword exsists.
    static bool containsKeyword(string name);

    /**
     * doCommand(string[])
     */

};

#endif //PROG1PROJECT_CONSTSDB_H
