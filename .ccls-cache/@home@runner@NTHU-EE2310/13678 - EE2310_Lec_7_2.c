#include <stdio.h>
#include <stdlib.h>

char* allocmore(char *array, int n);

int main()
{
	char *array = (char*)malloc(10*sizeof(char));
	char bufint, n = 0, alloced = 10;
	while(scanf("%c",&bufint)==1 && bufint!='\n'){
		array[n++] = bufint;
		//if n == 10, then double the array with allocmore
		if(n == alloced - 1) {
			array = (char*)allocmore(array, n+10);
			alloced = n+10;
		}
	}
	for(int i = 0; i < n; i++) {
		printf("%c", array[i]);
	}
	printf("\n");

	for(int i = 0; i < n; i++) {
		if(array[i] != array[n-i-1]) {
			printf("not a palindrome\n");
			return 0;
		}
	}
	printf("a palindrome\n");
	free(array);
	return 0;
}

char* allocmore(char *array, int n) {
	char *new_array = (char*)malloc(n*sizeof(char));
	for(int i = 0; i < n; i++) {
			new_array[i] = array[i];
	}
	free(array);
	return new_array;
}
