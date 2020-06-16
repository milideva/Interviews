#include <stdio.h>

int main() {
        int i = -5;

	printf("unsigned %u\n",i);
	return 0;
}
/*
   When converting from a signed integer to an unsigned integer whose length is equal to or longer than the original type, then if the signed value was nonnegative, its value is unchanged. If the value was negative, then it is converted to the signed form of the longer type and then made unsigned by conceptually adding it to one greater than the maximum that can be held in the unsigned type. In a twos complement system, this preserves the original bit-pattern for positive numbers and guarantees ?sign-extension? of negative numbers.
   Taking a 16-bit int for an example, the unsigned version has a range of 0?65535. Converting a signed value of -7 to this type involves adding 65536, resulting in 65529. 

   */
