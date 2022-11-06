#include <stdio.h>

int main()
{
    int layers;
    scanf("%d", &layers);
    for(int i = 1; i <= layers; i++) {
        for(int j = 0; j <= layers - i - 1; j++) {
            printf(" ");
        }
        for(int h = 0; h < i; h++) {
            printf("%s%d", h == 0? "": " ", i);
        }
        printf("\n");
    }
    

    return 0;
}