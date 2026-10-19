#include "element.h"
#include "parsing_utils.h"
#include <string>


#ifndef OPERATION_H
#define OPERATION_H

class Operation: public Element {
    std::string operatorToken = ADD_OPERATOR;
    Element* left = nullptr;
    Element* right = nullptr;

    public:
        Operation(const string& operationToken);

        virtual double Value() const;
        virtual int IntValue() const;
        virtual double DoubleValue() const;

        Element Calculate() const;
};

#endif