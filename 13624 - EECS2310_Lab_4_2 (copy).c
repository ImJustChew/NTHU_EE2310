#include <stdio.h>

int main()
{
    int input;
    int factors[360];
    int factpoint = 0;
    int currentdiv = 2;
    
    scanf("%d", &input);
    
    while(1) {
        if(input % currentdiv == 0) {
            factors[factpoint] = currentdiv;
            input /= currentdiv;
            factpoint++;
        }
        else if(input == 1){
						if(factpoint == 0) {
							factors[0] = 1;
							factpoint++;
						}
            break;
        }
        else {
            currentdiv++;
        }
    }
    
    for(int i = 0; i< factpoint; i++) {
        if(i != 0) printf("*");
        printf("%d", factors[i]);
    }
    
    printf("\n");

    return 0;
}
