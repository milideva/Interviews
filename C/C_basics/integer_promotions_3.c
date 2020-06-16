
#include <stdio.h>

/*
   In C99, integer promotion is clearly defined in following rule (6.3.1.1):

   If an int can represent all values of the original type, the value is
   converted to an int; otherwise, it is converted to an unsigned int. These
   are called the integer promotions. All other types are unchanged by the
   integer promotions.
   
   signed char: -127 to 127
   unsigned char: 0 to 255
   signed short: -32767 to 32767
   unsigned short: 0 to 65535
   signed int: -2147483647 to 2147483647
   
   Please note that it's VALUE preserving and NOT sign preserving.
   Thus unsigned char can get promoted to int (not unsigned int).
   
   unsigned char can range from 0 to 255(*), and an int can indeed represent
   all those values.
   
   This is not true for machines where short and int are of same size.
   
   signed char <= short <= int <= long
   
   (sizeof(char)=sizeof(int)) is a real-life scenario for those programming
   something like 16-bit TI DSPs, where the minimum addressable unit of data
   memory is 16 bit, so no 8-bit chars.

*/

int main(void)
{
    unsigned char a = 0xff;
    char b = 0xff;
    printf("A: %08x, B: %08x\n", a, b);

/*
  unsigned char a = 0xff is presenting 255. However, char b = 0xff is
  presenting -1. When both converted to int type, a remains 255, or
  0x000000ff; b will be 0xffffffff which is -1 represented in int type.
*/

    int c = a + b;

    printf("A: %08x, B: %08x, C = A+B = %08x\n", a, b, c);

    return 0;
}
