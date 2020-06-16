#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

typedef unsigned int uint;
typedef struct heap_tag heap_t;

struct heap_tag {
    uint heap_curr_size;
    uint heap_max_size;
    uint heap_arr[0];
};

// root is at index 1 not at index 0
uint parent (uint i) {
    return i/2;
}

uint left (uint i) {
    return 2*i;
}

uint right (uint i) {
    return 2*i+1;
}

/* Root is at 1st element of the array, 0th element is unsed. */
int getMin (heap_t  *heap) {
    return heap->heap_arr[1]; 
}

heap_t *allocate_heap (uint max_size) {
    heap_t *heap = calloc(1, sizeof(*heap) + max_size * sizeof heap->heap_arr[0] );
    if (!heap) return NULL;
    heap->heap_max_size = max_size;
    return heap;
}

static void swap (heap_t *heap, int i, int j) {
    uint temp  = heap->heap_arr[i];
    heap->heap_arr[i] = heap->heap_arr[j];
    heap->heap_arr[j] = temp;
}

// Insert at the last element and then go up to root swapping if required.
bool insert_min (heap_t *heap, int elem) {
    if (heap->heap_curr_size+1 >= heap->heap_max_size) {
        return false;
    }
    heap->heap_curr_size++;
    /* Insert at the end */
    heap->heap_arr[heap->heap_curr_size] = elem;

    int i = heap->heap_curr_size;
    while (i >= 0 && heap->heap_arr[i] < heap->heap_arr[parent(i)]) {
        swap(heap, i, parent(i));
        i = parent(i);
    }
    return true;
}

void heapify_min (heap_t *heap, int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    printf("i[%d]:%d,  l[%d]:%d r[%d]:%d\n", i, heap->heap_arr[i], l, heap->heap_arr[l], r, heap->heap_arr[r]);

    // Compare the smallest with left child and swap index if left is smaller
    if (l < heap->heap_curr_size && heap->heap_arr[l] < heap->heap_arr[i]) {
        smallest = l;
    }
    // Compare right with new smallest now
    if (r < heap->heap_curr_size && heap->heap_arr[r] < heap->heap_arr[smallest]) {
        smallest = r;
    }
    if (smallest != i) {
        // actual swap is here, recurse and repeat
        swap(heap, i, smallest);
        heapify_min(heap, smallest);
    }
}

int extract_min (heap_t *heap) {
    if (heap->heap_curr_size <= 0) 
      return INT_MAX;
    if (heap->heap_curr_size == 1) {
        heap->heap_curr_size--; 
        return getMin(heap);
    }

    int ret = getMin(heap);

    /* Remove root, move last elem into root and call heapify_min() */
    heap->heap_arr[1] = heap->heap_arr[heap->heap_curr_size];
    heap->heap_curr_size--;
    
    heapify_min(heap, 1);

    return ret;
}

void print_heap (heap_t *heap) {
    uint i, p, prev_p=0;
    for (i=1; i<= heap->heap_curr_size; i++) {
        if (prev_p != parent(i)) printf("\n");
        printf("[%d][p:%d]:%u:", i, parent(i), heap->heap_arr[i]);
        prev_p = parent(i);
    }
    printf("\n------------------\n\n");
}

heap_t *init (uint max_heap_size) {
    return allocate_heap(max_heap_size);
}
void test (heap_t *heap) {
    insert_min(heap, 500);
    insert_min(heap, 300);
    insert_min(heap, 200);
    insert_min(heap, 1500);
    insert_min(heap, 800);
    insert_min(heap, 178);
    insert_min(heap, 534);
    insert_min(heap, 6353);

    print_heap(heap);

    uint elem = extract_min(heap);
    printf("\n Removed min: %u\n", elem);
    
    print_heap(heap);
}
int main (void) {
    heap_t *heap = init(64);
    test(heap);
}
