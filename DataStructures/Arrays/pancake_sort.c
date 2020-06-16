/*

Given an unsorted array, sort the given array. You are allowed to do only following operation on array.

flip(arr, i): Reverse all array elements from 0 to i 

*/

#include <stdio.h>

void flip (int arr[], unsigned int i) {
    int j = 0;
    while (j < i) {
        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
        j++;
        i--;
    }
}

/* Find index of max element in arr[0..index]
*/
unsigned int find_max_index (int arr[], unsigned int index) {
    int max = arr[0];
    unsigned max_index = 0;
    for (int i = 1; i < index; i++) {
        if (arr[i] > max) {
            max = arr[i];
            max_index = i;
        }
    }
    return max_index;
}

void pancakeSort (int arr[], int size) {

    int n = size;

    while (n > 1) {

        int max_index = find_max_index(arr, n);
        if (max_index != n-1) {
            // Move the max to the end and reduce size (exclude it) 
            flip(arr, max_index);
            flip(arr, n-1);
        }
        n--;
    }

}

void printArray(int arr[], int n) { 
    for (int i = 0; i < n; ++i) 
        printf("%d ", arr[i]); 
} 

int main() { 
    int arr[] = {23, 10, 20, 11, 12, 6, 7}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
  
    pancakeSort(arr, n); 
  
    puts("Sorted Array "); 
    printArray(arr, n); 
  
    puts("\n");
    return 0; 
} 

