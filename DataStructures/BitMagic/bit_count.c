#include <stdio.h>

static unsigned int 
bit_count (unsigned int v) {
    // count the number of bits set in v
    unsigned int c; // c accumulates the total bits set in v

    for (c = 0; v; c++) {
        v &= v - 1; // clear the least significant bit set
    }

    return c;
}

int main (void) {
    unsigned int a = 11;
    printf("num_bits in %d (0x%x) is %d\n", a, a, bit_count(a)); 

    a = 8;
    printf("num_bits in %d (0x%x) is %d\n", a, a, bit_count(a));

    return 0;
}
