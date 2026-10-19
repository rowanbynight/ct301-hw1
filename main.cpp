#include "element.h"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <stdbool.h>
#include <bits/stdc++.h>
#include <fstream>
#include "parsing_utils.h"
#include "operation.h"
using namespace std;


// The run methods return their error codes
int run_usage_mode() {
    cout << "Usage: Enter either a filename to parse "
        "or an equation to be parsed in the format of "
        "\"Left_Element Operator Right_Element\"" << endl;
    return 1;
}

int run_terminal_mode(char** argv) {
    string left = argv[1];
    string op = argv[2];
    string right = argv[3];
    try {
        validate_operand_token(left);
        validate_operand_token(right);
        validate_operator_token(op);
        cout << Element(left).Calculate(Element(right), op) << endl;
    }
    catch (InvalidElement &e) {
        cerr << e.what() << endl;
        return 3;
    }
    catch (InvalidOperator &e) {
        cerr << e.what() << endl;
        return 4;
    }
    catch (domain_error &e) {
        cerr << e.what() << endl;
        return 5;
    }
    return 0;
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
        if (next_line.size() == 0) {
            continue;
        }
        ParseOperationToken(next_line, a, b, op);
        try {
            validate_operand_token(a);
            validate_operand_token(b);
            validate_operator_token(op);
            cout << Element(a).Calculate(Element(b), op) << endl;
        }
        catch (exception &e) {
            cerr << "Error occured while calculating line " << i << endl;
            return i + 2;
        }
        i++;
    }
    return 0;
}

int run_tests() {
    Element newElement(4.5);
    cout << newElement.DoubleValue() << endl;   // 4.5
    cout << newElement.Value() << endl;         // 4.5
    cout << newElement.IntValue() << endl;      // 4
    newElement.ChangeType();
    cout << newElement.Value() << endl;         // 4
    newElement.ChangeType(false);
    cout << newElement.Value() << endl;         // 4
    newElement.ChangeType(true);                
    cout << newElement.Value() << endl;         // 4.5
    newElement.Value(5);
    cout << newElement.DoubleValue() << endl;   // 5
    cout << newElement.Value() << endl;         // 5
    cout << newElement.IntValue() << endl;      // 5
    cout << (Element(4) + Element(5)).Value() << endl;          // 9
    cout << (Element(4) + Element(5)).IsDouble() << endl;       // 0
    cout << (Element(4) + Element(5.5)).Value() << endl;        // 9.5
    cout << (Element(4) + Element(5.5)).IsDouble() << endl;     // 1
    cout << (Element(3.5) + Element(5.5)).Value() << endl;      // 9
    cout << (Element(3.5) + Element(5.5)).IsDouble() << endl;   // 1
    cout << (Element(43) % Element(5)).Value() << endl;         // 3
    cout << Element(5) + 4 << endl;     // 9
    cout << 4 + Element(5) << endl;     // 9
    cout << Element(3.5) + 5.5 << endl; // 9
    cout << 3.5 + Element(5.5) << endl; // 9
    cout << Element(5) + 4.5 << endl;   // 9.5
    cout << 4.5 + Element(5) << endl;   // 9.5
    cout << Element(5.5) + 4 << endl;   // 9.5
    cout << 4 + Element(5.5) << endl;   // 9.5

    Operation* op = new Operation(string("14 + 5"));
    cout << op->Calculate() << endl;
    op = new Operation("4 * 5");
    cout << op->Calculate() << endl;
    op = new Operation("42 % 5");
    cout << op->Calculate() << endl;
    op = new Operation("4 / 0");
    try {
        cout << op->Calculate() << endl;
    }
    catch (domain_error& e) {
        cout << e.what() << endl;
    }

    Element e1 = *(new Element(4));
    Element e2 = *(new Element(5));
    Element e3 = *(e2.Clone());
    cout << e1 * e2 << endl;        // 20
    cout << e1 * e3 << endl;        // 20
    e3.Value(6);
    cout << e1 * e2 << endl;        // 20
    cout << e1 * e3 << endl;        // 24
    
    Operation o1 = *(new Operation(e1, "*", e2));
    Operation o2 = *(new Operation(e1, "*", e3));
    cout << o1.Calculate() << endl;                 // 20
    cout << o2.Calculate() << endl;                 // 24
    o1.SetOperator("+");
    o2.SetOperator("-");
    cout << o1.Calculate() << endl;                 // 9
    cout << o2.Calculate() << endl;                 // -2

    Operation o3 = o1;
    cout << o1.Calculate() << endl;                 // 9
    cout << o3.Calculate() << endl;                 // 9
    o3.SetOperator("*");
    cout << o1.Calculate() << endl;                 // 9
    cout << o3.Calculate() << endl;                 // 20

    o1 = Operation("4 + 5");
    o2 = Operation("4 + 5.1");
    o3 = Operation("4.2 + 5.1");
    cout << o1.IsDouble() << endl;
    cout << o2.IsDouble() << endl;
    cout << o3.IsDouble() << endl;
    cout << o1.Calculate() << endl;
    cout << o2.Calculate() << endl;
    cout << o3.Calculate() << endl;
    return 0;
}

bool test = true;

int main(int argc, char** argv) {
    if (test) {
        return run_tests();
    }
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