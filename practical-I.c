#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    int len = strlen(str);
    if (len >= 2 && str[len - 1] == 'b' && str[len - 2] == 'b' && strspn(str, "a") == len - 2) {
        printf("Valid string \n", str);
    } else {
        printf("Invalid string \n", str);
    }

    return 0;
}
