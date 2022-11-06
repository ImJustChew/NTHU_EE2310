#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int m, n;
	scanf("%d %d\n", &m, &n);
	char** matrix = (char**)malloc(m * sizeof(char*));
	for (int i = 0; i < m; i++) {
		matrix[i] = (char*)malloc(n * sizeof(char));
		for (int j = 0; j < n; j++) {
			char temp;	
			do {
				scanf("%c", &temp);
			}
			while(temp == '\n');
			matrix[i][j] = temp;
		}
		}
	char** ansmatrix = (char**)malloc(m * sizeof(char*));

	for(int i = 0; i < m; i++) {
		ansmatrix[i] = (char*)malloc(n * sizeof(char));
		for(int j = 0; j < n; j++) {
			if(matrix[i][j] == '1') ansmatrix[i][j] = '#';
			else {
				int sum = 0;
				if(i - 1 >= 0 && j - 1 >= 0 && matrix[i - 1][j - 1] == '1') sum += 1;
				if(i - 1 >= 0 && j + 1 < n && matrix[i - 1][j + 1] == '1') sum += 1;
				if(i + 1 < m && j - 1 >= 0 && matrix[i + 1][j - 1] == '1') sum += 1;
				if(i + 1 < m && j + 1 < n && matrix[i + 1][j + 1] == '1') sum += 1;
				if(i - 1 >= 0 && matrix[i - 1][j] == '1') sum += 1;
				if(i + 1 < m && matrix[i + 1][j] == '1') sum += 1;
				if(j - 1 >= 0 && matrix[i][j - 1] == '1') sum += 1;
				if(j + 1 < n && matrix[i][j + 1] == '1') sum += 1;
				ansmatrix[i][j] = sum == 0?'.': sum + '0';
			}
		}
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			printf("%c", ansmatrix[i][j]);
		}
		printf("\n");
	}
  return 0;
}