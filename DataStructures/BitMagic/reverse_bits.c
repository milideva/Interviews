#include <stdio.h>
#include <limits.h>

unsigned int reverse_bits (unsigned int v) {
    unsigned int r = 0;
    unsigned int mask;

    mask = 0x1;
    
    int i = sizeof(v) * CHAR_BIT;

    while (i) {
        if (v & mask) {
            r |= (0x1 << (i-1)); 
        }
        mask <<= 1;            
        i--;
    }
    
   return r;
}

int main (void) {
 
    unsigned int v = 0x22;
    unsigned int r;

    r = reverse_bits(v);
    printf("Input:0x%x, Reversed:0x%x\n", v, r);

    return 0;
}
