
#include <stdio.h>

/* Count trailing zeros (ctz) __builtin_ctz. */

/* Use gdb : set output-radix 16
   p/t to print in binary 
*/

int BitScanLow_BranchFree(unsigned int value)
{
    int i16 = !(value & 0xffff) << 4;
    value >>= i16;

    int i8 = !(value & 0xff) << 3;
    value >>= i8;

    int i4 = !(value & 0xf) << 2;
    value >>= i4;

    int i2 = !(value & 0x3) << 1;
    value >>= i2;

    int i1 = !(value & 0x1);

    int i0 = (value >> i1) & 1? 0 : -32;

    return i16 + i8 + i4 + i2 + i1 + i0;
}


int main (void) {
    unsigned int value = 0x80000008;

    printf("value:0x%x, #lsb:%d\n", value, BitScanLow_BranchFree(value));
    printf("value:0x%x, __builtin_ctz #lsb:%d\n", value, __builtin_ctz(value));

    return 0;
}
