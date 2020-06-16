/*
  Detect if two integers have opposite signs
*/

#include <stdbool.h>
#include <stdio.h>

/*
  bit0  bit1   XOR
  0     0      0
  0     1      1
  1     0      1
  1     1      0
*/
bool opposite_signs (int a, int b) {
    int result = a ^ b;
    if (result < 0) return true;
    return false;
}    

int main (void) {
    int a, b;

    a = 1;
    b = -1;

    printf("a=%d b:%d \t opposite sign:%s\n", a, b, 
           opposite_signs(a,b) ? "true" : "false");

    a = -1;
    b = -1;

    printf("a=%d b:%d \t opposite sign:%s\n", a, b, 
           opposite_signs(a,b) ? "true" : "false");

    a = 1;
    b = 1;

    printf("a=%d b:%d \t opposite sign:%s\n", a, b, 
           opposite_signs(a,b) ? "true" : "false");

    return 0;
}
