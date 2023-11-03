%{
#include <iostream>
#include <cstring>
using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE* yyin;

int yyerror(const char* s) {
    cerr << "Parser error: " << s << endl;
    return 1;
}

%}

%union {
    int num;
    char str[100];
}

%token <num> NUMBER
%token <str> IDENTIFIER
%token VAR EQUAL PLUS MINUS MULTIPLY DIVIDE OPEN_PAREN CLOSE_PAREN NEWLINE
%left PLUS MINUS
%left MULTIPLY DIVIDE
%nonassoc UMINUS

%start program
%type <num> expression term factor

%%

program : statement_list
        ;

statement_list : statement
               | statement_list NEWLINE statement
               ;

statement : VAR IDENTIFIER EQUAL expression
          | expression
          ;

expression : term
           | expression PLUS term
           | expression MINUS term
           ;

term : factor
     | term MULTIPLY factor
     | term DIVIDE factor
     ;

factor : NUMBER
       | IDENTIFIER
       | OPEN_PAREN expression CLOSE_PAREN
       | MINUS factor %prec UMINUS
       ;

%%

int main() {
    yyin = fopen("input.txt", "r");
    yyparse();
    fclose(yyin);
    return 0;
}
