/* 	
A Product Array Puzzle (google)

Given an array arr[] of n integers, construct a Product Array prod[] (of 
same size) such that prod[i] is equal to the product of all the elements 
of arr[] except arr[i]. 

********** Solve it without division operator and in O(n). ************

Example:
arr[] = {10, 3, 5, 6, 2}
prod[] = {180, 600, 360, 300, 900}

Algorithm:
1) Construct a temporary array left[] such that left[i] contains product 
of all elements on left of arr[i] excluding arr[i].
2) Construct another temporary array right[] such that right[i] contains 
product of all elements on on right of arr[i] excluding arr[i].
3) To get prod[], multiply left[] and right[].

*/


static int *productArray (int arr[], int n) {

  int *left = malloc(sizeof(int)*n);
  int *right = malloc(sizeof(int)*n);
  int *prod = malloc(sizeof(int)*n);
  int i, j;

  left[0] = right[n-1] = 1;

  for (i=1; i<n; i++) {
	left[i] = left[i-1] * arr[i-1];
  }

  for (j=n-2; j>=0; j--) {
        right[j] = right[j+1] * arr[j+1];
  }

  for (i=0; i<n; i++) {
	prod[i] = left[i] * right [i];
  }

  for (i=0; i<n; i++)
    printf("prod[%d]:%d ", i,prod[i]);

  free(left); free(right);

  return prod;
}

int main() {
  int arr[] = {10, 3, 5, 6, 2};
  int i, n = sizeof(arr)/sizeof(arr[0]);
  
  for (i=0; i<n; i++)
    printf("arr[%d]:%d ", i, arr[i]);

  printf("\nThe product array is: \n");
  productArray(arr, n);
  getchar();
}
