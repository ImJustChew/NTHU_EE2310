#include <stdio.h>
#include <string.h>
int main()
{
    int inputs[255];
    int inputlen = 0;
    
    for (int i = 0; i < sizeof(inputs); i ++) {
        int cur;
        scanf("%d", &cur);
        if(cur == -1) {
            inputlen = i;
            break;
        }
        else {
            inputs[i] = cur;
        }
    }
    
    int inversions = 0;
    for(int i = 0; i < inputlen; i++) {
        for(int j = i; j < inputlen; j++) {
            if(inputs[j] < inputs[i]) {
                if(inversions != 0) printf(", ");
                printf("%d>%d", inputs[i], inputs[j]);
                inversions++;
            }
        }
    }
    if(inversions != 0)printf("\n");
    
    printf("%d inversion(s)\n", inversions);
    
    

    return 0;
}
