#include <stdio.h>

void input(char [][10], int, int);
void count(char [][10], char [][10], int , int);
void output(char [][10], int, int);

int main(){
   int  h, w;
   char a[10][10];
   char b[10][10];

   scanf("%d %d", &h, &w);

   input(a,h,w);
   count(a,b,h,w);
   output(b,h,w);

    
   return 0;
}

void input(char a[][10], int h, int w) {
   int i, j;
   char temp;
   //printf( "Enter the minefield:\n");
    for (i=0; i<h; i++){
       scanf("\n");

       for (j=0; j<w; j++){
         //scanf("%c", &a[i][j]);
           scanf("%c", &temp);
           if('1' == temp){
               a[i][j] = (char)1;
           }
           if('0'== temp){
               a[i][j] = (char)0;
           }
             
       }
    }
}

void count(char a[][10] , char b[][10] , int h , int w) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(a[i][j] == 1) b[i][j] = '#';
            else {
                int sum = 0;
                if(j > 0 &&             a[i][j-1] == 1) sum++; //LEFT
                if(j < w -1  &&             a[i][j+1] == 1) sum++; //RIGHT;
                if(i > 0 &&             a[i-1][j] == 1) sum++; //TOP
                if(i < h -1 &&             a[i+1][j] == 1) sum++; //BOTTOM;
                if(i > 0 && j >0 &&     a[i-1][j-1] == 1) sum++; //TOP LEFT
                if(i > 0 && j < w -1 &&    a[i-1][j+1] == 1) sum++; //TOP RIGHT;
                if(j > 0 && i < h -1 &&    a[i+1][j-1] == 1) sum++; //BOTTOM LEFT
                if(i < h -1 && j < w -1 &&    a[i+1][j+1] == 1) sum++; //BOTTOM RIGHT;
                b[i][j] = sum == 0?'.':(sum +'0');
            }
        }
    }
}

void output(char b[][10] , int h , int w) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            printf("%c", b[i][j]);
        }
        printf("\n");
    }
    
}
