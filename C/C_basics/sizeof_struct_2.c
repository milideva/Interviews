#include <stdio.h>
#include <string.h>

struct struct_arr {
	int  i;
	char c;
        /* There is a 3 byte structure hole */
};
typedef struct struct_arr struct_arr_t;

char *cptr = "devdatta";
char char_arr[] = "devdatta";

int main () {
	struct_arr_t a[10];

	printf("sizeof(a[0])=%ld\n", sizeof(a[0]));

	a[0] = a[1]; // structs can be assigned to. no memcpy needed.
		     // Can not be compared against each other due to holes.

        /* 
           This is the reason why structs have holes. 
           There could be an array of structs.
           So if there is 'no hole', then the next struct array element
           would have int i on unaligned if it followed char c of prev elem
           without hole.
         */

        printf("Char ptr sizeof(\"%s\")=%d, strlen(\"%s\")=%d\n", 
                cptr, sizeof(cptr),
                cptr, strlen(cptr));

        printf("Char array sizeof(\"%s\")=%d, strlen(\"%s\")=%d\n", 
                char_arr, sizeof(char_arr), char_arr, strlen(char_arr));
        return 0;
}

