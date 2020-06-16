#include<stdio.h>

int array[] = {23,34,12,17,204,99,16};

#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))

int main()  {      
        int d;
        /* SURPRISE !!!!!!!!!
           d is int and compared with unsigned int returned by sizeof
           This causes d to be promoted to unsigned!
           If either operand is unsigned, the signed operand is converted
           to unsigned - in ANSI as well as K&R.
           */
        printf("printing all %d elements of array start:\n", TOTAL_ELEMENTS);
        for( d = -1; d <= TOTAL_ELEMENTS; d++)          
        	printf("%d\n",array[d+1]);
        printf("printed all %d elements of array end\n", TOTAL_ELEMENTS);
        /* Do not mix signed and unsigned */
        /* -Wall does not warn, -Wsign-compare does most of the times */

      return 0;  
}
