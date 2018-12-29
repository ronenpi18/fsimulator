//
// created
//
#ifndef PROG1PROJECT_ENVIROMENT_H
#define PROG1PROJECT_ENVIROMENT_H

#include <string>

/**
 * this class is for controling the interpreter - easily operate it,
 * no matter if its file or command line.
 */
class Enviroment {

private:
    const std::string EXCEPTION_WAS_THROWN = "EXCEPTION was thrown !";
public:


    // do the main operation on the command line option.
    void CommandlineOperation();


    // interperat script from file named fileName.
    void runScriptFromFile(std::string& fileName);

    ~Enviroment();
};


#endif //PROG1PROJECT_ENVIROMENT_H
