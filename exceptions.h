#include <string>


#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


using namespace std;


class InvalidElement: public std::invalid_argument {
    public:
        InvalidElement(string what): std::invalid_argument(what) {}
};

class InvalidOperator: public std::invalid_argument {
    public:
        InvalidOperator(string what): std::invalid_argument(what) {}
}; 

class DivideByZeroError: public std::domain_error {
    public:
        DivideByZeroError(string what): std::domain_error(what) {}
};

class ModuloByDoubleError: public std::domain_error {
    public:
        ModuloByDoubleError(string what): std::domain_error(what) {}
};

#endif