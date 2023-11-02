#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

enum TokenType {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    PUNCTUATION,
    KEYWORD,
    UNKNOWN
};

struct Token {
    TokenType type;
    string value;
};

class Lexer {
public:
    Lexer(const string& filename) {
        input.open(filename);
        if (!input.is_open()) {
            cerr << "Error opening file: " << filename << endl;
        }
    }

    ~Lexer() {
        input.close();
    }

    Token getNextToken() {
        Token token;
        char currentChar = input.get();

        while (isspace(currentChar)) {
            currentChar = input.get();
        }

        if (isalpha(currentChar)) {
            token.type = IDENTIFIER;
            while (isalnum(currentChar) || currentChar == '_') {
                token.value += currentChar;
                currentChar = input.get();
            }

            if (isKeyword(token.value)) {
                token.type = KEYWORD;
            }
        } else if (isdigit(currentChar)) {
            token.type = NUMBER;
            while (isdigit(currentChar)) {
                token.value += currentChar;
                currentChar = input.get();
            }
        } else if (isOperator(currentChar)) {
            token.type = OPERATOR;
            token.value = currentChar;
            currentChar = input.get();
        } else if (isPunctuation(currentChar)) {
            token.type = PUNCTUATION;
            token.value = currentChar;
            currentChar = input.get();
        } else if (currentChar == EOF) {
            token.type = UNKNOWN;
        } else {
            token.type = UNKNOWN;
            token.value = currentChar;
            currentChar = input.get();
        }

        return token;
    }

private:
    ifstream input;

    bool isKeyword(const string& word) {
        return false;
    }

    bool isOperator(char ch) {
        return false;
    }

    bool isPunctuation(char ch) {
        return false;
    }
};

int main() {
    Lexer lexer("your_source_code.txt");

    Token token = lexer.getNextToken();
    while (token.type != UNKNOWN) {
        cout << "Type: " << token.type << ", Value: " << token.value << endl;
        token = lexer.getNextToken();
    }

    return 0;
}
