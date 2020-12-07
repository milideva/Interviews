#include <stdio.h>
#include <stdlib.h>

// 8765 a[0]=8 ... a[3]=5 
int increment_by_one (unsigned int array[], int size) {
    if (size <= 0) return -1;

    unsigned int carry = 1;

    for (int i = size-1; i>=0; i--) {
        if (array[i] < 0) 
            return -1;
        array[i] += carry;
        if (array[i] < 10) {
            return size;
        }
        array[i] = 0;
    }
    unsigned int *aptr = malloc(sizeof *aptr * (size+1));
    for (int i=1; i < size+1; i++) {
        aptr[i] = array[i-1];
    }
    aptr[0] = 1;

    array = aptr;
    return size+1;
}


int main () {
    unsigned int a3[3] = { 9, 9, 9 };
    unsigned int *a = &a3[0];
    int sz = sizeof a3 / sizeof a3[0];
    int new_sz = increment_by_one(a, sz);
    if (new_sz < 0) return -1;
    if (new_sz == sz+1) printf("size increased\n");
    else printf("same size\n");
    return 0;
}

