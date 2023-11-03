{
int COMMENT=0;
%}
identifier [a-zA-Z][a-zA-Z0-9]*
%%
#.*\n {printf("%sThis is a PREPROCESSOR DIRECTIVE\n",yytext);}
auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|f
or|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|t
ypedef|union|unsigned|void|volatile|while {printf("\n%s is a 
KEYWORD",yytext);}
"/*" {COMMENT = 1;}
"*/" {COMMENT = 0;}
{identifier}\( {if(!COMMENT)printf("\nFUNCTION: \n%s",yytext);}
{identifier}(\[[0-9]*\])? {if(!COMMENT) printf("\n%s is an 
IDENTIFIER",yytext);}
