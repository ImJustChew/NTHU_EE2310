#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n;
    int arr1[10][10];
    scanf("%d %d", &m, &n);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &arr1[i][j]);
        }
    }
    int a, b;
    int arr2[10][10];
    scanf("%d %d", &a, &b);
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            scanf("%d", &arr2[i][j]);
        }
    }
    int f1 = m, f2 = b;
    int mult[10][10];
    for(int j = 0; j < f2; j++) {
        for(int i = 0; i < f1; i++) {
            mult[i][j] = 0;
            for(int k = 0; k < n; k++) {
                mult[i][j] += arr1[i][k]*arr2[k][j];
            }
        }
    }
    for(int i = 0; i < f1; i++) {
        for(int j = 0; j < f2; j++) {
            printf("%d", mult[i][j]);
            if(j < f2-1) printf(" ");
        }
        printf("\n");
    }


    return 0;
}
