#include <stdio.h>
 
/*
  Output:

  a = ?
  b = ?
  Not Same 

  When we print a and b, same character is printed, but when we compare them,
  we get the output as "Not Same".  "a" and "b" have same binary
  representation as char. But when comparison operation is performed on "a" 
  and "b", they are first converted to int. "a" is a signed char, when it is
  converted to int, its value becomes -5 (signed value of 0xfb). "b" is
  unsigned char, when it is converted to int, its value becomes 251. The
  values -5 and 251 have different representations as int, so we get the
  output as "Not Same".
*/
int main()
{
    char a;
    unsigned char b;
    
    a = b = 0xfb;
 
    printf("a = %c in hex:%x\n", a, a);
    printf("b = %c in hex:%x\n", b, b);
 
    if (a == b)
      printf("\nSame\n");
    else
      printf("\nNot Same\n");
    return 0;
}
