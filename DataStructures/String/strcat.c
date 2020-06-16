#include <strings.h>

int makestring (char *ret_str, int str_len) {
	char buffer[8];
	int i, len;

	memset(ret_str, 0, str_len);

	for (i=200; i<205; i++) {
		memset(buffer, 0, sizeof buffer);
		len = snprintf(buffer,sizeof buffer, "%x", i);
		if (str_len - len < 0) {
			return 0;
		}
		strncat(ret_str, buffer, str_len);
		str_len -= len;
		
		printf("buffer: %s str_len %d\n", ret_str, str_len);
	}
	return 1;
}

int main() {

	char buffer[32]; // Can support 16 sg
	(void) makestring(buffer, sizeof buffer);
	printf("buffer: %s str_len %d\n", buffer, strlen(buffer));	
}
