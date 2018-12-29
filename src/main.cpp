#include <iostream>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Interpreter.h"

using namespace std;;
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "Databases/SymbolsDB.h"
#include "Enviroment.h"
#include "Utils.h"

int main(int argc, char *argv[]) {

    Enviroment *e = new Enviroment;
    try {

        // by if the user inserted a filename or not, do the right operation.
        if (argc <= 1) {
            e->CommandlineOperation();

        }

        else {
            string fileName = string(argv[1]);
            e->runScriptFromFile(fileName);
        }
        delete e;
        exit(0);
    } catch (...)  {
        delete e;
        exit(1);
    }


}