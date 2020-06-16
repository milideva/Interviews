#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

/* shifting moves in zero.s, we need 'rotate' with rotated bits coming back in from the other side */
unsigned int rotate_left (unsigned int i, unsigned int shift) {
    unsigned int ret, max_bits;
    
    max_bits = (sizeof(i) * CHAR_BIT);
    printf("\n%s: number:0x%x:shift:%d\n", __FUNCTION__, i, shift);
    if (shift >= max_bits) {
        return i;
    }

    ret = i << shift;

    ret = ret | (i >> (max_bits-shift));

    return ret;

}

/* shift right on int, is implementation defined.
   on unsigned int, it moves in 0
*/
unsigned int rotate_right (unsigned int i, unsigned int shift) {
    unsigned int ret, max_bits;
    
    max_bits = sizeof(i) * CHAR_BIT;
    printf("\n%s: number:0x%x:shift:%d\n", __FUNCTION__, i, shift);
    if (shift >= max_bits) {
        return i;
    }

    ret = i >> shift;

    ret = ret | (i << (max_bits-shift));

    return ret;

}

static bool is_bit_set (unsigned int i, unsigned int pos) {
    if (i & (1 << pos)) return true;
    return false;
}

static void print_binary (unsigned int i) {
    unsigned int max_bits = (sizeof(i) * CHAR_BIT);
    
    printf("\n%s: number:0x%x:\t", __FUNCTION__, i);
    while (max_bits) {
        printf("%s", is_bit_set(i, max_bits-1) ? "1" : "0");
        max_bits--;
        if (max_bits % 4) continue;
        printf(" ");
    }

    printf("\n");
}

int main (void) {

    unsigned int i = 0x34;

    print_binary(i);

    i = rotate_left(i, 30);
    print_binary(i);

    i = rotate_right(i, 30);
    print_binary(i);

    return 0;
}
