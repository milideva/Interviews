/*
26. Remove Duplicates from Sorted Array

Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same. Then return the number of unique elements in nums.

Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:

Change the array nums such that the first k elements of nums contain the unique elements in the order they were present in nums initially. The remaining elements of nums are not important as well as the size of nums.
Return k.

*/
#include <stdio.h>

/* Array must be sorted */
int remove_duplicates (int array[], int size) {
    int wr = 0; // write pointer points to uniq

    for (int i = 1; i < size; i++) {
        if (array[i] != array[wr]) {
            wr++;
            array[wr] = array[i];
        }
    }
    return wr + 1; // new array size.
}
        
void print_array (int array[], int size, char *stringToPrint) {
    int i;
    printf("\n%s array[%d] : ", stringToPrint, size);
    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
    
int main () {
    /* Array must be sorted */

    int array[] = { 0, 0, 0, 2, 2, 55, 56, 56, 200, 200, 201,201};
    print_array(array, sizeof array / sizeof array[0], "Before removing duplicates: ");

    int count = remove_duplicates(array, sizeof array/sizeof array[0]);
    print_array(array, count, "After removing duplicates: ");

    return 0;
}
