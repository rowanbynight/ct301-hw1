#include "element.h"
#include <iostream>
#include <ostream>
#include <string>
#include <stdbool.h>
#include <bits/stdc++.h>
#include <fstream>


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
    if (this->isDouble || right.isDouble) {
        return Element(this->DoubleValue() / right.DoubleValue());
    }
    return Element(this->IntValue() / right.IntValue());
}

Element Element::operator%(Element const &right) {
    if (this->isDouble || right.isDouble) {
        throw std::invalid_argument("Math error: Cannot perform modulo arithmetic on non-integers");
    }
    return Element(this->IntValue() % right.IntValue());
}