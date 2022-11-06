#include <stdio.h>
int main(){
   char temp_c, str[21];
   int i=0, len=1;
   do{ // getting input from user
     scanf("%c", &temp_c);
     if(temp_c!=' ' && temp_c!='\n')
       str[i++] = temp_c;
   } while(temp_c!=' ' && temp_c!='\n' && i<21);
   len = i; //current i is string length
   
   /*
    your palindrome logic
   */
	for(int i = 0; i < len; i++) {
		if(str[i] != str[len-i-1]) {
			printf("not a palindrome\n");
			return 0;
		}
	}
	printf("a palindrome\n");
   return 0;
}