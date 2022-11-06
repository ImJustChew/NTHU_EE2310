#include <stdio.h>

int main() {
    char input;
    scanf("%c", &input);
    printf("You've entered %c. Its ASCII code is %d.\n", input, (int)input);
    return 0;
}
