#include <memory.h>
#include <string.h>
#include <stdio.h>

#define STR "123456"
char str1[17] = STR;

/* See the difference between memcpy and memmove */

int main()
{

   printf( "The string: %s\n", str1 );
   memcpy( (str1+6), str1, 10 );
   printf( "New string: %s\n", str1 );

   memset(str1, sizeof(str1), 0);
   char *new = STR;
   strncpy( str1, new, strlen(new)+1 );   // reset string

   printf( "The string: %s\n", str1 );
   memmove( (str1+6), str1, 10 );
   printf( "New string: %s\n", str1 );

}
