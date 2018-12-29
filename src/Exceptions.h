//
// created by omri & gal on 12/25/18.
//

#ifndef PROG1PROJECT_EXCEPTIONS_H
#define PROG1PROJECT_EXCEPTIONS_H

#include <exception>
#include <string>
using namespace std;

class BasicException : public exception{
protected:
    string _message;

public :
    BasicException(string message):
            _message(message) {}

    virtual const char* what() const throw() {
        return _message.c_str();
    }
    virtual ~BasicException() {

    }

};


class SymbolException : public BasicException{
public :
    SymbolException(string message):
            BasicException(message) {};
};


class DevisionByZeroException: public BasicException{
public :
    DevisionByZeroException(string m):
    BasicException(m) {};
};



class ServerException : public BasicException{
public :
    ServerException(string message):
    BasicException(message) {};
};


class FlightsServerException : public BasicException{
public :
    FlightsServerException(string message):
    BasicException(message) {};
};

class KeywordException : public BasicException{
public :
    KeywordException(string message):
    BasicException(message) {};
};


class BadArgumentsException : public BasicException{
public :
    BadArgumentsException(string message):
    BasicException(message) {};
};

class BracketsException : public BasicException{
public :
    BracketsException(string message):
            BasicException(message) {};
};


class CommandException : public BasicException{
public :
    CommandException(string message):
            BasicException(message) {};
};

class ConditionalException : public BasicException{
public :
    ConditionalException(string message):
            BasicException(message) {};
};


#endif //PROG1PROJECT_EXCEPTIONS_H
