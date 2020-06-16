#include <stdio.h>

int sv = -5; //signed val -5 is 0xfffffffb
unsigned int uv = 0xffFFff00;

/* MUST BE unsigned int */
int count_bits (unsigned int val) {
	int count = 0;
	while (val) {
		val &= (val-1);	
		count++;
	}
	return count;
}
int main () {
	unsigned int val;

	val = sv < 0 ? -sv : sv;

    printf("val:%d parity:%d\n", sv, count_bits(sv));
	printf("abs val:%d parity:%d\n", sv, count_bits(val));
	printf("val:%u parity:%d\n", uv, count_bits(uv));
	return 0;
}
