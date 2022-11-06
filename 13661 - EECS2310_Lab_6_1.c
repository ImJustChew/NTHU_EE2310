#include <stdio.h>

int main()
{
    int n;
    int a[100][100];
    scanf("%d", &n);
    
    for(int i =0; i < n ; i++){
        for(int j = 0; j< n; j++){
            scanf("%d", &a[i][j]);
        }
    }
    
    for(int i =0; i < n ; i++){
        for(int j = 0; j< n; j++){
            for(int q=0; q<= i; q++) {
                for(int k=0; k < j; k ++){
                    if(a[q][k]== a[i][j]){
                        printf("yes\n");
                        return 0;
                    }
                }
            }
        }
    }
    printf("no\n");
    return 0;
}
