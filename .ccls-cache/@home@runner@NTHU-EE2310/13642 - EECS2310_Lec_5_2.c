#include <stdio.h>

void swap(int *a, int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int main(void) {
  int x, y;
  scanf("%d %d", &x, &y);

  swap(&x,&y);
  printf("x=%d, y=%d\n", x, y);
 
  return 0;
}