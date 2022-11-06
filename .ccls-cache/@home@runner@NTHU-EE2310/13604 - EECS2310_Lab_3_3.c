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

//2021/1/1 is friday


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
    
    switch(daysago % 7) {
        case 0: printf("Thursday\n"); break;
        case 1: printf("Friday\n"); break;
        case 2: printf("Saturday\n"); break;
        case 3: printf("Sunday\n"); break;
        case 4: printf("Monday\n"); break;
        case 5: printf("Tuesday\n"); break;
        case 6: printf("Wednesday\n"); break;
    }

    return 0;
}