

/*

Given an array where every element occurs three times, except one element
which occurs only once. Find the element that occurs once. Expected time
complexity is O(n) and O(1) extra space.  Examples:

Input: arr[] = {12, 1, 12, 3, 12, 1, 1, 2, 3, 3}
Output: 2

http://www.geeksforgeeks.org/find-the-element-that-appears-once/


*/

#include <stdio.h>
#include <limits.h>

int find_one_occurence_element (int arr[], int size) {
    int i, pos, result, count, mask;
    
    result = INT_MAX;


    for (pos = 0; pos < sizeof(int)*CHAR_BIT; pos++) {
        mask = 0x1 << pos;
        count = 0;
        for (i=0; i<size; i++) {
            if (arr[i] & mask) {
                count++;
            }
        }
        if (count %3) {
            if (result == INT_MAX) result = mask;
            else result |= mask;
        }
    }

    if (result == INT_MAX) return -1;

    return result;
}

void print_array (int arr[], int size) {
    int i;
    printf("Input array is : ");
    for (i=0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main (void) {
    int arr[] = {12, 1, 12, 3, 12, 1, 1, 2, 3, 3};
    int size = sizeof(arr)/sizeof(arr[0]);

    print_array(arr, size);
    int result = find_one_occurence_element(arr, size);
    printf("Following element occurs only once :%d \n", result);
    return 0;
}
