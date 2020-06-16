#include <stdio.h>
#include <string.h>

static void reverse_string(char *str)
{
	if (!str)
		return;

	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (i >= len/2)
			return;
		char temp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = temp;
	}

}

int main (void) 
{

	char str[] = "devdatta"; // strlen is 9 including \0
	printf("Original string:%s\n", str);
	reverse_string(str);
	printf("Reversed string:%s\n", str);
	return 0;
}
