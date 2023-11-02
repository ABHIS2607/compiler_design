#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>

using namespace std;

bool isKeyword(const string &word) {
    vector<string> keywords = {"if", "else", "while", "int", "float", "return"};

    for (const auto &keyword : keywords) {
        if (word == keyword) {
            return true;
        }
    }

    return false;
}

bool isNumeric(const string &token) {
    for (char ch : token) {
        if (!isdigit(ch) && ch != '.') {
            return false;
        }
    }

    return true;
}

bool isBoolean(const string &token) {
    return token == "true" || token == "false";
}

bool isPointerLiteral(const string &token) {
    return token == "nullptr";
}

bool isStringLiteral(const string &token) {
    return token.front() == '"' && token.back() == '"';
}

bool isCharLiteral(const string &token) {
    return token.front() == '\'' && token.back() == '\'';
}

bool isUserDefinedLiteral(const string &token) {
    // Simplified check, you may need more specific logic
    return token.back() == 'i'; // Assumes user-defined literals end with 'i'
}

bool isOperator(const string &token) {
    // Add more operators as needed
    vector<string> operators = {"+", "-", "*", "/", "=="};

    for (const auto &op : operators) {
        if (token == op) {
            return true;
        }
    }

    return false;
}

bool isPunctuator(const string &token) {
    // Add more punctuators as needed
    vector<string> punctuators = {";", "{", "}", "(", ")"};

    for (const auto &punc : punctuators) {
        if (token == punc) {
            return true;
        }
    }

    return false;
}

int main() {
    string sourceCode;
    cout << "Enter the source program:\n";
    getline(cin, sourceCode);

    istringstream stream(sourceCode);
    string token;

    while (stream >> token) {
        if (isKeyword(token)) {
            cout << "Keyword: " << token << endl;
        } else if (isNumeric(token)) {
            cout << "Numeric: " << token << endl;
        } else if (isBoolean(token)) {
            cout << "Boolean: " << token << endl;
        } else if (isPointerLiteral(token)) {
            cout << "Pointer Literal: " << token << endl;
        } else if (isStringLiteral(token)) {
            cout << "String Literal: " << token << endl;
        } else if (isCharLiteral(token)) {
            cout << "Char Literal: " << token << endl;
        } else if (isUserDefinedLiteral(token)) {
            cout << "User-Defined Literal: " << token << endl;
        } else if (isOperator(token)) {
            cout << "Operator: " << token << endl;
        } else if (isPunctuator(token)) {
            cout << "Punctuator: " << token << endl;
        } else {
            cout << "Identifier: " << token << endl;
        }
    }

    return 0;
}
