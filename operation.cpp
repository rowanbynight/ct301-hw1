#include "element.h"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <stdbool.h>
#include <bits/stdc++.h>
#include <fstream>
#include "parsing_utils.h"
#include "operation.h"


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

Operation::Operation(const Element& left, char operator, const Element& right) {
    this->operatorToken = operator;
    this->left = left.Clone();
    this->right = right.Clone();
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