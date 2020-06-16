
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void sort (int* arr, int sz) {
    
    for (int i = 0; i < sz-1; i++) {
        for (int j = i+1; j < sz; j++) {
            if (arr[i] < arr[j])
                continue;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

bool search (int arr[], int sz, int key) {
    int low = 0;
    int high = sz;
    
    while (low <= high) {
        int mid = (low+high)/2;
        if (arr[mid] == key) return true;
        if (key > arr[mid]) {
            low = mid + 1;
            continue;
        }
        high = mid - 1;
    }
    return  false;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int *it1, *it2;
    int sz1, sz2;
    
    // it1 smaller, it2 bigger
    if (nums1Size > nums2Size) {
        it1 = nums2; it2 = nums1;
        sz1 = nums2Size; sz2 = nums1Size;
        *returnSize = nums2Size;
    } else {
        it1 = nums1; it2 = nums2;
        sz2 = nums2Size; sz1 = nums1Size;
        *returnSize = nums1Size;
    }
    // sort smaller
    sort(it1, sz1);

    int *arr = calloc(*returnSize, sizeof *arr);
    int j = 0;
    // walk through longer array one at a time 
    for (int i = 0; i < sz2; i++) {
        // search in sorted smaller array
        if (search(it1, sz1, it2[i])) {
            bool dup = false;
            // check in resulting array for duplicates
            for (int k = 0; k < j; k++) {           
                if (arr[k] == it2[i]) {
                    dup = true;
                    break;
                }
            }
            if (!dup)
                arr[j++] = it2[i];
        }       
    }
    *returnSize = j;
    return arr;
}


int main () {
    int arr1[] = {4, 9, 5};
    int arr2[] = {9, 4, 9, 8, 4};
    int sz = 0;
    int sz1 = sizeof arr1/sizeof arr1[0];
    int sz2 = sizeof arr2/sizeof arr2[0];

    int *arr = intersection(arr1, sz1, arr2, sz2, &sz);
    for (int i = 0; i < sz; i++) {
        printf("intersection array [%d] = %d\n", i, arr[i]);
    }
}
