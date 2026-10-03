#include <stdbool.h>
#include <ostream>

#ifndef ELEMENT_H
#define ELEMENT_H

class Element {
    bool isDouble = true;
    double value = 0;

    public:
        Element() {}
        
        Element(int value) {
            this->value = value;
            isDouble = false;
        }
        
        Element(double value) {
            this->value = value;
        }

        double Value() const;
        int IntValue() const;
        double DoubleValue() const;
        bool IsDouble() const;
        void ChangeType();
        void ChangeType(bool shouldBeDouble);
        void Value(double newVal);

        Element operator+(Element const &right);
        Element operator-(Element const &right);
        Element operator*(Element const &right);
        Element operator/(Element const &right);
        Element operator%(Element const &right);
};

#endif