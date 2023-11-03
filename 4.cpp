#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;

class Interpreter {
public:
    Interpreter() {}

    void interpret(const string& code) {
        lexer = istringstream(code);
        currentToken = getNextToken();
        while (currentToken.type != TokenType::EOF_TOKEN) {
            if (currentToken.type == TokenType::NEWLINE) {
                consume(TokenType::NEWLINE);
            } else {
                cout << evaluateExpression() << endl;
            }
        }
    }

private:
    enum class TokenType {
        NUMBER,
        IDENTIFIER,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        EQUAL,
        NEWLINE,
        VAR,
        EOF_TOKEN,
        OPEN_PAREN,
        CLOSE_PAREN
    };

    struct Token {
        TokenType type;
        string lexeme;
        double value;
    };

    istringstream lexer;
    Token currentToken;
    unordered_map<string, double> variables;

    Token getNextToken() {
        Token token;
        lexer >> token.lexeme;
        if (token.lexeme == "var") {
            token.type = TokenType::VAR;
        } else if (token.lexeme == "=") {
            token.type = TokenType::EQUAL;
        } else if (token.lexeme == "+") {
            token.type = TokenType::PLUS;
        } else if (token.lexeme == "-") {
            token.type = TokenType::MINUS;
        } else if (token.lexeme == "*") {
            token.type = TokenType::MULTIPLY;
        } else if (token.lexeme == "/") {
            token.type = TokenType::DIVIDE;
        } else if (token.lexeme == "\n") {
            token.type = TokenType::NEWLINE;
        } else if (isalpha(token.lexeme[0])) {
            token.type = TokenType::IDENTIFIER;
        } else if (isdigit(token.lexeme[0])) {
            token.type = TokenType::NUMBER;
            token.value = stod(token.lexeme);
        } else if (token.lexeme == "(") {
            token.type = TokenType::OPEN_PAREN;
        } else if (token.lexeme == ")") {
            token.type = TokenType::CLOSE_PAREN;
        } else {
            token.type = TokenType::EOF_TOKEN;
        }
        return token;
    }

    void consume(TokenType expectedType) {
        if (currentToken.type == expectedType) {
            currentToken = getNextToken();
        } else {
            cerr << "Error: Unexpected token type" << endl;
        }
    }

    double evaluateExpression() {
        double result = evaluateTerm();
        while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
            Token op = currentToken;
            if (op.type == TokenType::PLUS) {
                consume(TokenType::PLUS);
                result += evaluateTerm();
            } else if (op.type == TokenType::MINUS) {
                consume(TokenType::MINUS);
                result -= evaluateTerm();
            }
        }
        return result;
    }

    double evaluateTerm() {
        double result = evaluateFactor();
        while (currentToken.type == TokenType::MULTIPLY || currentToken.type == TokenType::DIVIDE) {
            Token op = currentToken;
            if (op.type == TokenType::MULTIPLY) {
                consume(TokenType::MULTIPLY);
                result *= evaluateFactor();
            } else if (op.type == TokenType::DIVIDE) {
                consume(TokenType::DIVIDE);
                double denominator = evaluateFactor();
                if (denominator != 0) {
                    result /= denominator;
                } else {
                    cerr << "Error: Division by zero" << endl;
                }
            }
        }
        return result;
    }

    double evaluateFactor() {
        if (currentToken.type == TokenType::NUMBER) {
            double value = currentToken.value;
            consume(TokenType::NUMBER);
            return value;
        } else if (currentToken.type == TokenType::IDENTIFIER) {
            string variableName = currentToken.lexeme;
            consume(TokenType::IDENTIFIER);

            if (variables.find(variableName) != variables.end()) {
                return variables[variableName];
            } else {
                cerr << "Error: Variable '" << variableName << "' not defined" << endl;
                return 0.0;
            }
        } else if (currentToken.type == TokenType::PLUS) {
            consume(TokenType::PLUS);
            return evaluateFactor();
        } else if (currentToken.type == TokenType::MINUS) {
            consume(TokenType::MINUS);
            return -evaluateFactor();
        } else if (currentToken.type == TokenType::VAR) {
            consume(TokenType::VAR);

            if (currentToken.type == TokenType::IDENTIFIER) {
                string variableName = currentToken.lexeme;
                consume(TokenType::IDENTIFIER);

                if (variables.find(variableName) == variables.end()) {
                    variables[variableName] = 0.0;
                } else {
                    cerr << "Error: Variable '" << variableName << "' already declared" << endl;
                }

                if (currentToken.type == TokenType::EQUAL) {
                    consume(TokenType::EQUAL);
                    double value = evaluateExpression();
                    variables[variableName] = value;
                    return value;
                } else {
                    cerr << "Error: Expected '=' after variable declaration" << endl;
                }
            } else {
                cerr << "Error: Expected variable name after 'var'" << endl;
            }
        } else if (currentToken.type == TokenType::OPEN_PAREN) {
            consume(TokenType::OPEN_PAREN);
            double result = evaluateExpression();
            consume(TokenType::CLOSE_PAREN);
            return result;
        } else {
            cerr << "Error: Unexpected token type in factor" << endl;
            return 0.0;
        }
    }
};

int main() {
    string code = "var x = 5\nvar y = 10\nvar result = y / x\nresult";
    Interpreter interpreter;
    interpreter.interpret(code);

    return 0;
}
