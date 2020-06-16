/*
  Some data types like char , short int take less number of bytes than int,
  these data types are automatically promoted to int or unsigned int when an
  operation is performed on them. This is called integer promotion. For
  example no arithmetic calculation happens on smaller types like char, short
  and enum. They are first converted to int or unsigned int, and then
  arithmetic is done on them. If an int can represent all values of the
  original type, the value is converted to an int . Otherwise, it is converted
  to an unsigned int.
*/

#include <stdio.h>
int main()
{
    char a = 30, b = 40, c = 10;
    char d = (a * b) / c;
    printf ("%d \n", d);
/* 
   At first look, the expression (a*b)/c seems to cause arithmetic overflow
   because signed characters can have values only from -128 to 127 (in most of
   the C compilers), and the value of subexpression ?(a*b)? is 1200 which is
   greater than 128. But integer promotion happens here in arithmetic done on
   char types and we get the appropriate result without any overflow.
*/

    return 0;
}
