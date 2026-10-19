#include "element.h"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <stdbool.h>
#include <bits/stdc++.h>
#include <fstream>
#include "parsing_utils.h"


bool token_is_operator(std::string token) {
    if (token.size() != 1) {
        return false;
    }
    return (
        token == MLT_OPERATOR ||
        token == DIV_OPERATOR ||
        token == ADD_OPERATOR ||
        token == SUB_OPERATOR ||
        token == MOD_OPERATOR
    );
}

// currently doesn't catch cases like "123.45aaaa"
bool token_is_numeric(std::string token) {
    try {
        stod(token);
        return true;
    }
    catch (invalid_argument &e) {
        return false;
    }
}

void validate_operand_token(std::string token) {
    if (token_is_numeric(token)) {
        return;
    }
    throw InvalidElement("Operand invalid: " + token + " is not a number");
}

void validate_operator_token(std::string token) {
    if (token.size() != 1) {
        throw InvalidOperator("Operator invalid: " + token + " must be a single character");
    }
    if (!token_is_operator(token)) {
        throw InvalidOperator("Operator invalid: " + token + " does not match any valid operators");
    }
}

// Adapted from geeks for geeks article: https://www.geeksforgeeks.org/cpp/how-to-split-std::string-by-delimiter-in-cpp/
void ParseOperationToken(std::string operationToken, std::string &left, std::string &right, std::string &op) {
    std::stringstream line_stream(operationToken);
    std::string token;
    for (int i = 0; line_stream >> token; i++) {
        if (i == 0) {
            left = token;
        }
        if (i == 1) {
            op = token;
        }
        if (i == 2) {
            right = token;
        }
    }
}