#include <stdio.h>
int main() {
   unsigned int i, x;
   scanf("%d", &x);
   for ( i=1; i<= x; ++i ){
      if ( i != 5) {
      	printf( "%u", i );
      }
   }
   printf( "\nUsed continue to skip printing the value 5\n");
   return 0;
}