%{
#include <stdio.h>
#include "yacc.tab.h"
%}

%%
[0-9]+              { yylval = atoi(yytext); return NUMBER; }
[-+*/\n]            { return *yytext; }
[ \t]               ;   //Ignore whitespace
.                   { printf("Invalid character: %s\n",yytext); }


%%

int main() {

    yylex();
    return 0;
}
