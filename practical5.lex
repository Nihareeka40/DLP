%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_token(const char *type, const char *text) {
    printf("%s: %s\n", type, text);
}
%}

%option noyywrap

DIGIT        [0-9]+
ID           [a-zA-Z_][a-zA-Z0-9_]*
STRING       \"([^\\"]|\\.)*\"
CHAR         \'([^\\']|\\.)\'
OPERATOR     [+\-*/%=&|<>!^]
PUNCTUATION  [();,{}[\]\[\]]

%%

"int"|"float"|"char"|"return"|"void"|"long"|"struct"   { print_token("Keyword", yytext); }
{ID}           { print_token("Identifier", yytext); }
{DIGIT}        { print_token("Constant", yytext); }
{STRING}       { print_token("String", yytext); }
{CHAR}         { print_token("Character", yytext); }
{OPERATOR}+    { print_token("Operator", yytext); }
{PUNCTUATION}  { print_token("Punctuation", yytext); }

"//".*         { /* Ignore single-line comments */ }
"/*"(.|\n)*?"*/" { /* Ignore multi-line comments */ }

[ \t\r\n]+     { /* Ignore white spaces */ }
.              { printf("Lexical Error: %s\n", yytext); }  // Handle invalid characters

%%

int main() {
    FILE *file = fopen("input.c", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);
    return 0;
}
