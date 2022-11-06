
#include <stdio.h>

int days[] = {
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
};

int main()
{
    int m,d;
    scanf("%d/%d", &m, &d);
    
    if(m > 12 || d > days[m-1]) {
        printf("Input Error\n");
        return 0;
    }
    
    int daysago = 0;
    for(int i = 1; i < m; i++) {
        daysago += days[i-1];
    }
    daysago += d;
    printf("There %s %d %s\n", daysago == 1? "is": "are", daysago, daysago == 1? "day": "days");
    

    return 0;
}
