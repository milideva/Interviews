#include "foo_public.h"
#include <stdio.h>

/* Compile 
   gcc -std=c99 -Wall foo_private.c foo_public.c
 */
int main (void) {
    node_t *temp = allocate_s();
    printf("allocated %p\n", (void *) temp);
    free_s(temp);
}
 
