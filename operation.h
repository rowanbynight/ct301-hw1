#include <element.h>


#ifndef OPERATION_H
#define OPERATION_H

class Operation: public Element {
    public:
        const int ADD = 0;
        const int SUB = 1;
        const int MLT = 2;
        const int DIV = 3;
        const int MOD = 4;

        virtual double Value() const;
        virtual int IntValue() const;
        virtual double DoubleValue() const;
        virtual bool IsDouble() const;
        virtual void ChangeType();
        virtual void ChangeType(bool shouldBeDouble);

    private:
        int operator = 0;
        Element* left = nullptr;
        Element* right = nullptr;
}

#endif