%{
#include <stdio.h>
%}

%%

charusat      { printf("university"); }
.|\n         { printf("%s", yytext); }  /* Print other characters as they are */

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
