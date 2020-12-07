#include <stdio.h>
#include <stdbool.h>


// Given an array, find the first missing number 
// example [3 4 0 7 1] answewr 2
// Space should be O(1) 

// a = [ 15, 8, 5, 3, 4, 1,  0, 2, 7, 9, 10]
// answer 6


// Note when space constraint is O(1), only options are setting elements -ve or swap operations
// to store some state

int is_a_valid_index (int index, int size) {
    // ignore out of bounds
    return index >= 0 && index < size;
}

void print_array (int a[], int sz) {
    for (int i=0; i< sz; i++) {
        printf("[%d:%d] ", i, a[i]);
    }
    printf("\n");
}

int missing_smallest_postive_int (int a[], int size) {
    for (int i = 0; i < size; i++) {
        int correctPos = a[i];
        while (is_a_valid_index(correctPos, size) && a[correctPos] != a[i]) {
            // swap
            // print_array(a, size);
            printf("swapping i:%d correctPos:%d with %d \n", i, correctPos, a[correctPos]);
            int temp = a[correctPos];
            a[correctPos] = correctPos;
            a[i] = temp;
            correctPos = a[i];
        }
    }

    // print_array(a, size);

    for (int i = 0; i < size; i++) {
        if (a[i] != i) 
            return i;
    }
    return size; 
}

int main () {
    int a[] = {  15, 8, 5, 0, 3, 4, 1, 2, 7, 9, 10 };
    int size = sizeof a / sizeof a[0];

    int missing = missing_smallest_postive_int(a, size);

    printf("index : %d \n", missing);
    return 0;
}
