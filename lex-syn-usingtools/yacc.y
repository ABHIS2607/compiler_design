%{
#include <stdio.h>
int yylex(void);
%}
%token NUMBER
%left '+' '-'
%left '*' '/'
%%
calc: expr '\n' { printf("Result: %d\n", $1);
}
;
expr: NUMBER { $$ = $1; }
| expr '+' expr { $$ = $1 + $3; }
| expr '-' expr { $$ = $1 - $3; }
| expr '*' expr { $$ = $1 * $3; }
| expr '/' expr {
if ($3 != 0) {
$$ = $1 / $3;
} else {
fprintf(stderr, "Error: Division by zero\n");
$$ = 0;
}
}
;
%%

int main() {
yyparse();
return 0;
}

