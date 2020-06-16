#include <stdio.h>
/* Convert camelCase to underscore notation, do not add _ if first 
letter is caps */

int camelCaseToUnderscore (const char *in, char *out) {

        int iCount = 0, oCount = 0;
        if (in == NULL) {
                out[oCount] = '\0' ;
        }

        while(in[iCount] != '\0') {
                if (in[iCount] <= 'Z' && in[iCount] >= 'A') {
                        if (oCount != 0) {
                                out[oCount++] = '_';
                        }
                        out[oCount] = in[iCount] + ('a' - 'A');
                } else {
                        out[oCount] = in[iCount];
                }
                iCount++;
                oCount++;

        }
        out[oCount] = '\0' ;

        return oCount;
}

int main () {
	char *foo = "DevdattaAjgaonkar";
	char *bar;
	int len = strlen(foo) + 1;

	bar = malloc(len+len/2);
	if (!bar) return 0;

	camelCaseToUnderscore(foo, bar);
	printf("Input:%s Output:%s\n", foo, bar);

	free(bar);
	return 0;
}
