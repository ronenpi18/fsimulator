//
// created by omri & gal on 12/11/18.
//

#ifndef ADVANCED_PROGRAMIMNG_1_PROJECT_COMMAND_H
#define ADVANCED_PROGRAMIMNG_1_PROJECT_COMMAND_H

#include <string>
#include <vector>
using namespace std;
/**
 *  Command interface.
 *  we can do a command out of string array representing a command.
 */
 class Command {

 public:
     virtual void doCommand() = 0;
     virtual bool anotherArg(string& current) = 0;
     virtual bool goBackArg(string& current) = 0;
     virtual ~Command() {};

 };
#endif //ADVANCED_PROGRAMIMNG_1_PROJECT_COMMAND_H
