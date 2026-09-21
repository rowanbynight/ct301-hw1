#include <iostream>
#include <string>
#include <stdbool.h>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;


// Partially adapted from code from https://www.geeksforgeeks.org/cpp/string-find-in-cpp/
bool token_is_int(string token) {
    try {
        [[maybe_unused]]
        int as_int = stoi(token);
        return token.find('.') == string::npos;
    }
    catch (invalid_argument& e) {
        return false;
    }
}

// currently doesn't catch cases like "123.45aaaa"
bool token_is_numeric(string token) {
    try {
        stod(token);
        return true;
    }
    catch (invalid_argument& e) {
        return false;
    }
}

const string MLT_OPERATOR = "*";
const string DIV_OPERATOR = "/";
const string ADD_OPERATOR = "+";
const string SUB_OPERATOR = "-";
const string MOD_OPERATOR = "%";

bool token_is_operator(string token) {
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


int calculate(int a, int b, string operation) {
    if (operation == MLT_OPERATOR) {
        return a * b;
    }
    if (operation == DIV_OPERATOR) {
        if (b == 0) {
            throw invalid_argument("Invalid operand: cannot divide by zero");
        }
        return a / b;
    }
    if (operation == ADD_OPERATOR) {
        return a + b;
    }
    if (operation == SUB_OPERATOR) {
        return a - b;
    }
    if (operation == MOD_OPERATOR) {
        return a % b;
    }
    else {
        throw invalid_argument("Operation " + operation + " not supported for int math");
    }
}

double calculate(double a, double b, string operation) {
    if (operation == MLT_OPERATOR) {
        return a * b;
    }
    if (operation == DIV_OPERATOR) {
        if (b == 0.0) {
            throw invalid_argument("Invalid operand: cannot divide by zero");
        }
        return a / b;
    }
    if (operation == ADD_OPERATOR) {
        return a + b;
    }
    if (operation == SUB_OPERATOR) {
        return a - b;
    }
    else {
        throw invalid_argument("Invalid operation: " + operation + " not supported for double math");
    }
}

// Adapted from geeks for geeks article: https://www.geeksforgeeks.org/cpp/how-to-split-string-by-delimiter-in-cpp/
void parse_line(string line, string &a, string &b, string &op) {
    stringstream line_stream(line);
    string token;
    for (int i = 0; line_stream >> token; i++) {
        if (i == 0) {
            a = token;
        }
        if (i == 1) {
            op = token;
        }
        if (i == 2) {
            b = token;
        }
    }
}

string execute(string a, string b, string operation) {
    bool int_mode = true;
    int_mode = token_is_int(a) && token_is_int(b);
    if (int_mode) {
        return to_string(calculate(stoi(a), stoi(b), operation)); 
    }
    else {
        return to_string(calculate(stod(a), stod(b), operation));
    }
}


void validate_operand_token(string token) {
    if (token_is_numeric(token)) {
        return;
    }
    throw invalid_argument("Operand invalid: " + token + " is not a number");
}

void validate_operator_token(string token) {
    if (token.size() != 1) {
        throw invalid_argument("Operator invalid: " + token + " must be a single character");
    }
    if (!token_is_operator(token)) {
        throw invalid_argument("Operator invalid: " + token + " does not match any valid operators");
    }
}


// The run methods return their error codes

int run_usage_mode() {
    cout << "Usage: Enter either a filename to parse "
        "or an equation to be parsed in the format of "
        "\"Left_Element Operator Right_Element\"" << endl;
    return 1;
}

int run_terminal_mode(char** argv) {
    string a = argv[1];
    string op = argv[2];
    string b = argv[3];
    try {
        validate_operand_token(a);
    }
    catch (invalid_argument& e) {
        cerr << e.what() << endl;
        return 3;
    }
    try {
        validate_operand_token(b);
    }
    catch (invalid_argument& e) {
        cerr << e.what() << endl;
        return 5;
    }
    try {
        validate_operator_token(op);
        cout << execute(a, b, op) << endl;
        return 0;
    }
    catch (invalid_argument& e) {
        cerr << e.what() << endl;
        return 4;
    }
}

int run_file_mode(string filename) {
    ifstream file_input;
    file_input.open(filename);
    if (!file_input) {
        cerr << "Error opening file " << filename << endl;
        return 2;
    }
    string next_line;
    string a;
    string b;
    string op;
    int i = 1;
    while (getline(file_input, next_line)) {
        //cout << "calcing line " << next_line << endl;
        if (next_line.size() == 0) {
            continue;
        }
        parse_line(next_line, a, b, op);
        try {
            validate_operand_token(a);
            validate_operand_token(b);
            validate_operator_token(op);
            cout << execute(a, b, op) << endl;
        }
        catch (invalid_argument& e) {
            cerr << "Error occured while calculating line " << i << endl;
            return i + 2;
        }
        i++;
    }
    return 0;
}


int main(int argc, char** argv) {
    if (argc == 1) {
        return run_usage_mode();
    }
    if (argc == 2) {
        return run_file_mode(argv[1]);
    }
    if (argc == 4) {
        return run_terminal_mode(argv);
    }
    cerr << "Invalid input: unsupported number of arguments passed" << endl;
    return 2;
}