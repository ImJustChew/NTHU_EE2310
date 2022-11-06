#include <stdio.h>

int main()
{
    int a,b;
    scanf("%d %d", &a, &b);
    printf("%d %s %d\n", a, a == b ? "==": a > b? ">": "<", b);

    return 0;
}
