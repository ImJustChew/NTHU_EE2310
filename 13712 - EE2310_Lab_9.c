/* Implement MergeSort() using recursion */

/* Please use the recursion method described in this lab to do this. Otherwise you may lose points even PENALTY POINTS */

/* 請用上課教的遞迴方式寫，否則不但不得分還可能會被倒扣分數！！ */

#include <stdio.h>
#include <stdlib.h>

void merge(int *a, int start, int mid, int end){
	int size1 = mid - start + 1, size2 = end - mid;
	int *merged = (int*) malloc(sizeof(int) *(size1+size2));
	int *left = a + start, *right = a + mid + 1;
	int i = 0, j = 0, k = 0;
	while(i < size1 && j < size2){
		if(left[i] <= right[j]){
			merged[k++] = left[i++];
		
		} else {
			merged[k++] = right[j++];
		}
	}
	while(i < size1){
		merged[k++] = left[i++];
	}
	while(j < size2){
		merged[k++] = right[j++];
	}

	//copy back
	for(i = 0; i < size1+size2; i++){
		a[start + i] = merged[i];
	}
	free(merged);
	
}

void MergeSort(int *arr, int begin_pos, int end_pos){
	if(begin_pos < end_pos) {
		int mid = (begin_pos + end_pos) / 2;
		MergeSort(arr, begin_pos, mid);
		MergeSort(arr, mid + 1, end_pos);
		merge(arr, begin_pos, mid, end_pos);
	}
}

int main(){
   int *a,  size;

   //  input
   scanf("%d", &size);
   a = (int*) malloc(sizeof(int)*size);
   for(int i=0; i< size; i++){
      scanf("%d", a+i);
   }


   //  sort
   MergeSort(a, 0, size-1);

   //  output

   for(int i=0; i< size-1; i++)
      printf("%d ", a[i]);

   printf("%d\n", a[size-1]);
   return 0;
}
