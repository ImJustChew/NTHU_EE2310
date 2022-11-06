#include<stdio.h>

int is_a_leap_year(int y){
    return (y % 400 == 0) || (y % 100 != 0 && y % 4 == 0);
}

int input_check(int Year, int Month, int Day, int Is_a_Leap_Year){
    int days[] = {31,28+Is_a_Leap_Year,31,30,31,30,31,31,30,31,30,31};
    if(Year < 0) return 1;
    if(Month < 0 || Month > 12) return 1;
    if(Day < 0 || Day > days[Month - 1]) return 1;
    return 0;
}

void compare_days(int y1, int m1, int d1, int y2, int m2, int d2){
    int y1days[] = {31,28+is_a_leap_year(y1),31,30,31,30,31,31,30,31,30,31};
    int y2days[] = {31,28+is_a_leap_year(y2),31,30,31,30,31,31,30,31,30,31};
    long years_apart = 0;
    for(int i = y2; i < y1; i++) {
        years_apart += (365 + is_a_leap_year(i));
    }
    long offset_months = 0;
    for(int i = 0; i< m1 - 1;i++){
        offset_months += y1days[i];
    }
    for(int i = 0; i< m2 - 1;i++){
        offset_months -= y2days[i];
    }
    long offset_days = d1-d2;
    if((years_apart+offset_days+offset_months) == 0) {
        printf("You entered the same dates\n");
    }
    else printf("%d/%d/%d is %ld day(s) earlier\n", y2, m2, d2, years_apart+offset_days+offset_months);
    
}

int main() {
    int year1 =0, year2=0, month1 = 0, month2 = 0, day1 =0, day2 = 0;

    scanf("%d/%d/%d",&year1, &month1, &day1);
    if( input_check(year1, month1, day1, is_a_leap_year(year1)) ){
        printf("Invalid input 1\n");
        return 0;
    }

    scanf("%d/%d/%d",&year2, &month2, &day2);
    if( input_check(year2, month2, day2, is_a_leap_year(year2)) ){
        printf("Invalid input 2\n");
        return 0;
    }

    compare_days(year1, month1, day1, year2, month2, day2);

    return 0;
}

