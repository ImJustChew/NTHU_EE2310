#include <stdio.h>
#include <stdlib.h>

void merge(int* A, int* B, int* C, int n, int m)
{
	int i = 0, j = 0, k = 0;
	while (i < n && j < m)
	{
		if (A[i] < B[j])
		{
			C[k] = A[i];
			i++;
		}
		else
		{
			C[k] = B[j];
			j++;
		}
		k++;
	}
	while (i < n)
	{
		C[k] = A[i];
		i++;
		k++;
	}
	while (j < m)
	{
		C[k] = B[j];
		j++;
		k++;
	}
}

int main() {

	int n, m;
	scanf("%d", &n);
	int A[100];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &A[i]);
	}
	scanf("%d", &m);
	int B[100];
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &B[i]);
	}
	int C[200];
	merge(A, B, C, n, m);
	printf("%d\n", n + m);
	for (int i = 0; i < n + m; i++)
	{
		printf("%d", C[i]);
		if(i < (n + m -1)) printf(" ");
	}
	printf("\n");
	return 0;
}