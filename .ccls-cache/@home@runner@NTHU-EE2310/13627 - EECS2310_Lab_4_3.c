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
    int first = 1;
		int current = 0;
		int sum = 0;
    for(int i = 0; i< factpoint; i++) {
				if (i == 0) {
					current = factors[0];
				}
				if(factors[i] == current) {
					sum++;
				} else {
        	if(!first) printf("*");
        	printf("%d^%d", current, sum);
					current = factors[i];
					sum = 1;
					first = 0;
				}
    }
		int finalsum = 0;
		for(int i = 0; i< factpoint; i++) {
			if(current == factors[i]) {
				finalsum++;
			}
		}
		if(!first) printf("*");
		printf("%d^%d", current, finalsum);
    
    printf("\n");

    return 0;
}
