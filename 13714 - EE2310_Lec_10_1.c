#include <stdio.h>

int isPalindrome(char str[], int n, int x) {
	if(n == x) return 1;
	else {
		int next = isPalindrome(str, n, x+1);
		return str[x] == str[n-x-1] && next == 1;
	}
}

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
	if(!isPalindrome(str, len, 0)) printf("not a palindrome\n");
	else printf("a palindrome\n");
	return 0;
}