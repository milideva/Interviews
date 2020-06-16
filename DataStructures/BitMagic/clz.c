
#include <stdio.h>
#include <limits.h>

/* Count leading zeros (clz) __builtin_clz */

/* Use gdb : set output-radix 16
   p/t to print in binary 
*/

int clz (unsigned int value)
{
    unsigned int count = 0;
    unsigned int num_bits = sizeof value * CHAR_BIT;

    while (value) {
        value >>= 1;
        count++;
    }
    return num_bits - count;
}

void test (unsigned int value) {

    printf("value:0x%x, #lsb:%d\n", value, clz(value));
    printf("value:0x%x, __builtin_ctz #lsb:%d\n\n", 
           value, __builtin_clz(value));

}
int main (void) {
    unsigned int value = 0x80000008;
    test(value);

    value =  0x0000008;
    test(value);

    return 0;
}
