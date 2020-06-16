#include <stdio.h>
 
// Alignment requirements

/******* Struct alignment = alignment of its biggerst member ********/

/*
 http://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/

*/

// Alignment requirements
// (typical 32 bit machine)
 
// char         1 byte
// short int    2 bytes
// int          4 bytes
// double       8 bytes

// structure A
typedef struct structa_tag
{
   char        c;
   short int   s;
} structa_t;
 
// structure B
typedef struct structb_tag
{
   short int   s;
   char        c;
   int         i;
} structb_t;
 
// structure C
typedef struct structc_tag
{
   char        c;
   double      d;
   int         i;
} structc_t;
 
// structure D
typedef struct structd_tag
{
   double      d;
//   int         i;
   char        c;
    struct structc_tag structc;
} structd_t;
 
int main()
{
   printf("sizeof(structa_t) = %d\n", sizeof(structa_t));
   printf("sizeof(structb_t) = %d\n", sizeof(structb_t));


/*
structure C ? Every structure will also have alignment requirements

Applying same analysis, structc_t needs sizeof(char) + 7 byte padding +
sizeof(double) + sizeof(int) = 1 + 7 + 8 + 4 = 20 bytes. However, the
sizeof(structc_t) will be 24 bytes. It is because, along with structure
members, structure type variables will also have natural alignment. Let us
understand it by an example. Say, we declared an array of structc_t as shown
below

structc_t structc_array[3];

Assume, the base address of structc_array is 0×0000 for easy calculations. If
the structc_t occupies 20 (0×14) bytes as we calculated, the second structc_t
array element (indexed at 1) will be at 0×0000 + 0×0014 = 0×0014. It is the
start address of index 1 element of array. The double member of this structc_t
will be allocated on 0×0014 + 0×1 + 0×7 = 0x001C (decimal 28) which is not
multiple of 8 and conflicting with the alignment requirements of double. As we
mentioned on the top, the alignment requirement of double is 8 bytes.

Inorder to avoid such misalignment, compiler will introduce alignment
requirement to every structure. It will be as that of the largest member of
the structure. In our case alignment of structa_t is 2, structb_t is 4 and
structc_t is 8. If we need nested structures, the size of largest inner
structure will be the alignment of immediate larger structure.

In structc_t of the above program, there will be padding of 4 bytes after int
member to make the structure size multiple of its alignment. Thus the sizeof
(structc_t) is 24 bytes. It guarantees correct alignment in arrays.
*/
   printf("IMP sizeof(structc_t) = %d\n", sizeof(structc_t));

/* 
There is a way to minimize padding. The programmer should declare the
structure members in their increasing/decreasing order of size. An example is
structd_t given in our code, whose size is 16 bytes in lieu of 24 bytes of
structc_t.
*/
   printf("IMP sizeof(structd_t) = %d\n", sizeof(structd_t));
 
   return 0;
}
