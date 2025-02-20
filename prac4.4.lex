%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lower = 0, upper = 0, digit = 0, symbol = 0, length = 0;

void reset_flags() {
    lower = upper = digit = symbol = length = 0;
}
%}

%%

[a-z]    { lower = 1; length++; }
[A-Z]    { upper = 1; length++; }
[0-9]    { digit = 1; length++; }
[*;#$@]  { symbol = 1; length++; }
.        { length++; }  // Count any other characters
\n       { 
            if (length >= 9 && length <= 15 && lower && upper && digit && symbol) 
                printf("Valid password\n"); 
            else 
                printf("Invalid password\n"); 
            reset_flags();
         }
%%

int main() {
    printf("Enter a password to validate: ");
    yylex();
    return 0;
}

int yywrap() { return 1; }
