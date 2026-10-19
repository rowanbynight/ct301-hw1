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

        Operation(const Element& left, char op, const Element& right);

        Operation(const Element& left, std::string op, const Element& right);

        Operation(const Operation& original);

        virtual Element* Clone() const override; 

        virtual double Value() const;
        virtual int IntValue() const;
        virtual double DoubleValue() const;
        virtual bool IsDouble() const override;
        bool SetOperator(std::string newOperator);

        Operation& operator=(Operation other);
        Element Calculate() const;

        virtual ~Operation();
};

#endif