#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct foo {
    int len;
    int array[]; // This is an overlay, must be the last element of struct
//    int test; // wont compile
} foo_t;
#define NUM_ELEMENTS (5)

/* Following works but is not portable */
/* offsetof (<type>, <element>), if you had a variable
   static <type> T; then the expression &T.<element> should be a constant pointer expression. In other words, you cannot use offsetof to calculate the offset of an array element with non-constant index. 
*/
foo_t * struct_allocate (unsigned n_elements)
{
        unsigned long size = offsetof(struct foo, array[n_elements]);
        printf("VLA struct size for malloc using offsetof : %lu \n", size);
        return malloc(size);
}

int main () {

    foo_t *ptr;
    int i, size = sizeof(foo_t) + NUM_ELEMENTS * sizeof(ptr->array[0]); // One way to calculate size for VLA
    
    ptr = struct_allocate(NUM_ELEMENTS);

    if (!ptr)
        return -1;
    
    printf("sizeof stuct with VLA :%lu\n", sizeof(foo_t));
    printf("Malloc.ed size %d\n", size);
    ptr->len = NUM_ELEMENTS;

    for (i= 0; i < ptr->len ; i++) {
        ptr->array[i] = i;
        printf("array[%d] = %d\n", i, ptr->array[i]);
    }
   
    free(ptr);
    return 0;
}
