/*
  Write code to find #bits that need to be changed to change numA to numB.
  Assume both are unsigned int.

         XOR
  0   0   0
  0   1   1
  1   0   1
  1   1   0

*/
#include <stdio.h>

unsigned num_bits_to_change (unsigned a, unsigned b) {
    unsigned out = a ^ b;
    unsigned count = 0;

    while (out) {
        if (out & 0x1) count++;
        out = out >> 1;
    }

    return count;
}

void test (unsigned a, unsigned b) {
    unsigned count = num_bits_to_change(a, b);
    printf("from a:%u to b:%u change %u bits\n", a, b, count);
}

int main (void) {
    test(5, 7);
    test(7, 5);
    test(0, 8);
    test(0, 15);
    test(7, 15);
    test(3, 8);
    return 0;
}
