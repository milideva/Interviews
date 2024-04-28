
/*

K'th Smallest Element in Unsorted Array

Given an array and a number k where k is smaller than size of array, we need
to find the kth smallest element in the given array. It is given that all
array elements are distinct.

Examples:

Input: arr[] = {7, 10, 4, 3, 20, 15}
       k = 3
Output: 7

Input: arr[] = {7, 10, 4, 3, 20, 15}
       k = 4
Output: 10


http://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/

Method 1 (Simple Solution) 
==========

A Simple Solution is to sort the given array using a O(nlogn) sorting
algorithm like Merge Sort, Heap Sort, etc and return the element at index k-1
in the sorted array. Time Complexity of this solution is O(nLogn).

Method 2 (Using Min Heap)
==========

In a min heap, the keys of parent nodes are less than or equal to those of the
children and the lowest key is in the root node.

A simple optimization is to create a Min Heap of the all n elements and call
extractMin() k times.

O(n) for each insert , there are n inserts to n * O(log n)
Logn for the height of heap, times k extract min, so k * O(log n)
 
Time complexity of this solution is (k + n) * O(log n).


Method 3 (Using Max-Heap)
==========
In a max heap, the keys of parent nodes are always greater than or equal to
those of the children and the highest key is in the root node. 

Build a Max-Heap of the first k elements (arr[0] to arr[k-1]) => O(k)
For each next element (arr[k] to arr[n-1]), compare it with root of MaxHeap.
a) If the element is less than the root then make it root, call heapify for maxHeap
b) Else ignore it.
// The step 2 is O((n-k)*logk)

Finally, root of the MaxHeap is the kth smallest element.

Time complexity of this solution is O(k * log k+ (n-k) *  logk) = O(n * log k)

children :: left : 2n + 1 and right : 2n + 2 in a zero-based array. 

Method 4 (QuickSelect) 
==========

This is an optimization over method 1 if QuickSort is used as a sorting
algorithm in first step. In QuickSort, we pick a pivot element, then move the
pivot element to its correct position and partition the array around it. The
idea is, not to do complete quicksort, but stop at the point where pivot
itself is k'th smallest element. Also, not to recur for both left and right
sides of pivot, but recur for one of them according to the position of
pivot. The worst case time complexity of this method is O(n2), but it works in
O(n) on average.


*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct min_heap_ min_heap;

struct min_heap_ {
    int array_size; /* Max size */
    int heap_size; /* Last element */
    int array[0];
};

int parent (int i) {
    return (i-1)/2;
}
int left (int i) {
    return (2*i)+1;
}
int right (int i) {
    return (2*i)+2;
}

void swap (int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int get_min (min_heap *heap) {
    return heap->array[0];
}

// A recursive method to heapify a subtree with root at given index
// This method assumes that the subtrees are already heapified
void min_heapify (min_heap *heap, int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap->heap_size && heap->array[l] < heap->array[i])
        smallest = l;
    if (r < heap->heap_size && heap->array[r] < heap->array[smallest])
        smallest = r;
    if (smallest != i) {
        swap(&heap->array[i], &heap->array[smallest]);
        min_heapify(heap, smallest);
    }
}

min_heap *create_min_heap (int arr[], int sz) {
    min_heap *heap;
    int size = sizeof *heap + sizeof (heap->array[0]) * sz;
    heap = malloc(size);
    if (!heap) return heap;

    heap->array_size = sz;
    heap->heap_size = sz;

    memcpy(heap->array, arr, sz * sizeof(heap->array[0]));

    int i = (sz - 1)/2;
    while (i >= 0) {
        min_heapify(heap, i);
        i--;
    }
    return heap;
}

/* Remove min elem from heap, which is root */
int extract_min (min_heap *heap) {
    if (heap->heap_size == 0) return INT_MIN;
    
    int root = heap->array[0];

    // If there are more than 1 items, move the last item to root
    // and call heapify.
    if (heap->heap_size > 1)
    {
        heap->array[0] = heap->array[heap->heap_size-1];
        min_heapify(heap, 0);
    }
    heap->heap_size--;

    return root;
}

int kthSmallest (int arr[], int sz, int k) {
    int i;
    // Build a heap of n elements: O(n) time
    min_heap *heap = create_min_heap(arr, sz);
 
    // Do extract min (k-1) times
    for (i=0; i<k-1; i++)
        extract_min(heap);
 
    // Return root
    return get_min(heap);
}
 
int main() {
    int arr[] = {12, 3, 5, 7, 19};
    int n = sizeof(arr)/sizeof(arr[0]), k = 2;

    int i = n;
    printf("Input array: ");
    while (i>=0) {
        printf("%d ", arr[n-i]);
        i--;
    }
    
    printf("\nK'th (k=%d) smallest element is %d\n", 
           k, kthSmallest(arr, n, k));
    return 0;
}
