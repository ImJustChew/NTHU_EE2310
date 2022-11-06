#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n;
    int arr[10][10];
    scanf("%d %d", &m, &n);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d", arr[i][j]);
            if(j < n-1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
