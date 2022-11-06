#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n = 0;
    scanf("%d", &n);
    int *array = (int*)malloc(n*sizeof(int));
    
    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    int inv = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(array[i] > array[j]) {
            		if(inv > 0) printf(", ");
                printf("%d>%d", array[i], array[j]);
                inv += 1;
            }
        }
    }
    printf("\n");
    printf("%d inversion(s)\n", inv);
    free(array);
}
