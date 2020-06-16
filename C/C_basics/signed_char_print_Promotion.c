#include <stdio.h>

int main() {

	int i;	
	unsigned char c;
	c = 249;
	i = (signed char) c;

	printf("int i %d signed char c %d \n", i, (signed) c);
	return 0;
}

