//
// created by omri & gal on 12/16/18.
//
#include "SymbolsDB.h"

const double SymbolsDB::UNINTILIZED_VAR_DEFAULT = 0;
map<string, double> SymbolsDB::_symbolTable;
multimap<string, string> SymbolsDB::_bindTable;
FlightDataGetterSetter* SymbolsDB::_socketManager = nullptr;

double SymbolsDB::getSymbol(string symbolName) {
    // if symbol doesn't exsists, throw expception;

    // if it is a symbol describes an source path, get it from the flights server - last value, update the table.

    if (isSourceSymbol(symbolName))
    {
        _symbolTable[symbolName] = _socketManager->recieve("get " + getPath(symbolName));
    }

    if(_symbolTable.count(symbolName) == 0)
        throw SymbolException("Symbol "+ symbolName +" not Exists");

    // else, return the symbol at symbolName from table.

    return _symbolTable.at(symbolName);
}

void SymbolsDB::setBindedSymbolRecursivly(string symbolName, double symbolValue, map<string, bool> &markedVariables, bool update) {

    // check for if it is a path symbol, and if it is , it can be undefined at first ,else exception if undefined.
    if (isSourceSymbol(symbolName)) {
        _symbolTable[symbolName] = symbolValue;
    }

    else {
        // if there is no var named this name, throw exception.
        if (_symbolTable.count(symbolName) == 0) {
            throw SymbolException("Symbol " + symbolName + " not exists. can't assing to it.");
        }

        // else, update its value.
        else {
            _symbolTable.at(symbolName) = symbolValue;
        }
    }

    // if it is a symbol describes an source path, send a request to the server to set this symbol at thems also.

    if (isSourceSymbol(symbolName)) {
        if (update)
            _socketManager->send("set " + getPath(symbolName) + " " + to_string(symbolValue));
    }

    // if symbolName is binded to other variable, we will change the other also.

    if(_bindTable.count(symbolName) != 0) {

        try {
            markedVariables.at(symbolName);
        } catch (out_of_range) {

            pair<MMAPIterator, MMAPIterator> result = _bindTable.equal_range(symbolName);
            for (MMAPIterator it = result.first; it != result.second; it++) {
                string &other = it->second;

                _symbolTable.at(other) = symbolValue;

                //  if the other is source symbol change it in server.

                if (isSourceSymbol(other)) {
                    _socketManager->send("set " + getPath(other) + " " + to_string(symbolValue));
                }

                //add this variable to the map as marked
                markedVariables[symbolName] = true;

                //change all binded variables to other...
                setBindedSymbolRecursivly(other, symbolValue, markedVariables, update);
            }
        }
    }
}

void SymbolsDB::setLocalSymbol(string symbolName, double symbolValue) {
    map<string, bool> bindList;
    setBindedSymbolRecursivly(symbolName, symbolValue, bindList,!UPDATE_IN_SERVER);
}

void SymbolsDB::setSymbol(string symbolName, double symbolValue) {

    map<string, bool> bindList;
    setBindedSymbolRecursivly(symbolName, symbolValue, bindList, UPDATE_IN_SERVER);

}

vector<string> SymbolsDB::getSymbolsNames() {

    vector<string> v;

    // extract the symbols names from the map into a vector.
    for(map<string, double>::const_iterator it = _symbolTable.cbegin(); it != _symbolTable.cend(); ++it) {
        v.push_back(it->first);
    }

    return v;
}

bool SymbolsDB::isSourceSymbol(string token) {
    return (token.length() > 2 && token[0] == '"' && token[token.length() - 1] == '"');
}

string SymbolsDB::getPath(string sourceSymbolName) {

   if (sourceSymbolName.length() > 3) {
       sourceSymbolName =  sourceSymbolName.substr(1, sourceSymbolName.length() - 2);

       // if the path start with / , cancel it.
       if (sourceSymbolName[0] == '/')
           sourceSymbolName = sourceSymbolName.substr(1, sourceSymbolName.length() - 1);
   }
   return sourceSymbolName;
}



void SymbolsDB::removeSymbol(string symbolName) {
    map<string, double>::iterator it = _symbolTable.find(symbolName);
    _symbolTable.erase(symbolName);
}

bool SymbolsDB::containsSymbol(string symbolName) {
    return _symbolTable.count(symbolName) != 0;
}

void SymbolsDB::addSymbol(string symbolName) {
    _symbolTable[symbolName] = UNINTILIZED_VAR_DEFAULT;
}

bool SymbolsDB::isBinded(string var1, string var2) {

    // if one is binded to the other in the map, return true;

    if(_bindTable.count(var1) != 0) {
        pair<MMAPIterator, MMAPIterator> result = _bindTable.equal_range(var1);
        for (MMAPIterator it = result.first; it != result.second; it++) {
            string& other = it->second;
            if (other == var2) {
                return true;
            }
        }
    }

    return false;
}

void SymbolsDB::setSocket(int sockfd) {
    _socketManager = new FlightDataGetterSetter(sockfd);
}

FlightDataGetterSetter *SymbolsDB::get_socketManager() {
    return _socketManager;
}

void SymbolsDB::bind(string var1, string var2) {

//    if (!containsSymbol(var1) || !containsSymbol(var2))
//        throw ("Can't bind if left or right expression is not decrlared.");


    // adds var1, var2 to bind table and also var 2, var 1.
    _bindTable.insert(make_pair(var1,var2));
    _bindTable.insert(make_pair(var2, var1));
}