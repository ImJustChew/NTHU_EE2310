#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m;
    int arr[20];
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &arr[i]);
    }

    for(int checklen = 0; checklen <= m; checklen++) {
        int sum = 0;
        for(int i = 0; i < (m - checklen); i++) {
            sum += arr[checklen + i];
            if(sum == 0) {
                printf("yes\n");
                return 0;
            }
        }
    }
    printf("no\n");


    return 0;
}
