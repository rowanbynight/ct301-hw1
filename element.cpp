#include "element.h"
#include <iostream>
#include <ostream>
#include <string>
#include <stdbool.h>
#include <bits/stdc++.h>
#include <fstream>


bool Element::TokenIsDouble(std::string const token) {
        try {
            [[maybe_unused]]
            int as_int = stoi(token);
            return token.find('.') != std::string::npos;
        }
        catch (std::invalid_argument& e) {
            return true;
        }
    }

Element::Element(const std::string& newVal) {
    // Partially adapted from code from https://www.geeksforgeeks.org/cpp/string-find-in-cpp/
    this->isDouble = this->TokenIsDouble(newVal);
    if (this->isDouble) {
        this->Value(std::stod(newVal));
    }
    else {
        this->Value(std::stoi(newVal));
    }
}

double Element::Value() const {
    if (isDouble) {
        return this->DoubleValue();
    }
    else {
        return this->IntValue();
    }
}

int Element::IntValue() const {
    return static_cast<int>(this->value);
}

double Element::DoubleValue() const {
    return this->value;
}

bool Element::IsDouble() const {
    return this->isDouble;
}

void Element::ChangeType() {
    this->isDouble = !this->isDouble;
}

void Element::ChangeType(bool shouldBeDouble) {
    this->isDouble = shouldBeDouble;
}

void Element::Value(double newVal) {
    this->value = newVal;
}

Element Element::operator+(Element const &right) {
    if (this->isDouble || right.isDouble) {
        return Element(this->DoubleValue() + right.DoubleValue());
    }
    return Element(this->IntValue() + right.IntValue());
}

Element Element::operator-(Element const &right) {
    if (this->isDouble || right.isDouble) {
        return Element(this->DoubleValue() - right.DoubleValue());
    }
    return Element(this->IntValue() - right.IntValue());
}

Element Element::operator*(Element const &right) {
    if (this->isDouble || right.isDouble) {
        return Element(this->DoubleValue() * right.DoubleValue());
    }
    return Element(this->IntValue() * right.IntValue());
}

Element Element::operator/(Element const &right) {
    if (right == 0) {
        throw std::domain_error("Domain error: cannot divide by zero");
    }
    if (this->isDouble || right.isDouble) {
        return Element(this->DoubleValue() / right.DoubleValue());
    }
    return Element(this->IntValue() / right.IntValue());
}

Element Element::operator%(Element const &right) {
    if (this->isDouble || right.isDouble) {
        throw std::domain_error("Domain error: Cannot perform modulo arithmetic on non-integers");
    }
    if (right == 0) {
        throw std::domain_error("Domain error: cannot perform modulo with respect to zero");
    }
    return Element(this->IntValue() % right.IntValue());
}

bool Element::operator==(Element const &right) const {
    return this->Value() == right.Value();
}

bool Element::operator!=(Element const &right) const {
    return this->Value() != right.Value();
}

// Adapted from https://www.geeksforgeeks.org/cpp/overloading-stream-insertion-operators-c/
std::ostream &operator<<(std::ostream &out, const Element &element) {
    return out << element.Value();
}