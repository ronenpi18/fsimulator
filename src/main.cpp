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
#include "Common/EnvironmentVar.h"
#include "Common/Utils.h"

int main(int argc, char *argv[]) {

    EnvironmentVar *pVar = new EnvironmentVar;
    try {

        // by if the user inserted a filename or not, do the right operation.
        if (argc <= 1) {
            pVar->TetminalController();

        }

        else {
            string fileName = string(argv[1]);
            pVar->fileRunner(fileName);
        }
        delete pVar;
        exit(0);
    } catch (...)  {
        cout << "There was a problem in the Main function" << endl;
        delete pVar;
        exit(1);
    }
}