#include "element.h"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <stdbool.h>
#include <bits/stdc++.h>
#include <fstream>
#include "parsing_utils.h"
#include "operation.h"
#include <utility>


Operation::Operation(const string& operationToken) {
    std::string leftToken;
    std::string rightToken;
    ParseOperationToken(operationToken, leftToken, rightToken, this->operatorToken);
    // No need to catch here, since we haven't allocated anything yet
    validate_operand_token(leftToken);
    validate_operand_token(rightToken);
    validate_operator_token(this->operatorToken);
    // Now can allocate
    this->left = new Element(leftToken);
    this->right = new Element(rightToken);
}

Operation::Operation(const Element& left, char op, const Element& right) {
    this->operatorToken = op;
    this->left = new Element(left);
    this->right = new Element(right);
}

Operation::Operation(const Element& left, std::string op, const Element& right) {
    this->operatorToken = op;
    this->left = new Element(left);
    this->right = new Element(right);
}

Operation::Operation(const Operation& original): Element() {
    this->operatorToken = original.operatorToken;
    this->left = original.left->Clone();
    this->right = original.right->Clone();
}

Element* Operation::Clone() const {
    Element* newOperation = new Operation(*this);
    return newOperation;
}

Element Operation::Calculate() const {
    return this->left->Calculate(*(this->right), this->operatorToken);
}

double Operation::Value() const {
    if (this->IsDouble()) {
        return this->Calculate().DoubleValue();
    }
    else {
        return this->Calculate().IntValue();
    }
}

int Operation::IntValue() const {
    return this->Calculate().IntValue();
}

double Operation::DoubleValue() const {
    return this->Calculate().DoubleValue();
}

bool Operation::IsDouble() const {
    return left->IsDouble() || right->IsDouble();
}

bool Operation::SetOperator(std::string newOperator) {
    if (!token_is_operator(newOperator)) {
        return false;
    }
    this->operatorToken = newOperator;
    return true;
}

// There has to be a better way to do this, 
// but i couldnt figure out how to implement it with the swap function
Operation& Operation::operator=(Operation other) {
    this->operatorToken = other.operatorToken;
    this->left = other.left->Clone();
    this->right = other.right->Clone();
    return *this;
}

Operation::~Operation() {
    delete left;
    delete right;
}