#include <stdbool.h>
#include <ostream>
#include <string>

#ifndef ELEMENT_H
#define ELEMENT_H

class Element {
    bool isDouble = true;
    double value = 0;

    bool TokenIsDouble(std::string const token);

    public:
        Element() {}
        
        Element(int value) {
            this->value = value;
            this->isDouble = false;
        }
        
        Element(double value) {
            this->value = value;
        }

        Element(const std::string& newVal);

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
        bool operator==(Element const &right) const;
        bool operator!=(Element const &right) const;
};

#endif