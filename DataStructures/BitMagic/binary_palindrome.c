#include <stdbool.h>
#include <stdio.h>
#include <limits.h>


/*

 Check if binary representation of a number is palindrome Given an integer
 x, write a C function that returns true if binary representation of x is
 palindrome else return false.

 For example a numbers with binary representation as 10..01 is palindrome and
 number with binary representation as 10..00 is not palindrome.

 Note that input b1001 (dec 9) alone is not a palindrome for this question.

*/

bool is_binary_palindrome (unsigned int num) {
    unsigned int bits, rmask, lmask, rpos, lpos, rbit, lbit;
    bits = sizeof num * CHAR_BIT;
    
    lpos = 0;
    rpos = bits - 1;

    while (rpos > lpos) {
        rmask = 1 << rpos;
        lmask = 1 << lpos;
        
        rbit = (num & rmask) >> rpos;
        lbit = (num & lmask) >> lpos;
        
        if (rbit != lbit) return false;

        rpos -= 1;
        lpos += 1;
    }

    return true;
}



#define B(x) string_to_binary(#x)

unsigned int string_to_binary (const char *str) {
    unsigned long long i = 0;
    while (*str) {
        i <<= 1;
        i += *str++ - '0';
    }
    return i;
}

void test (unsigned int x) {
    printf("x:0x%x ", x);
    bool pali = is_binary_palindrome(x);
    printf("is_palindrome::%s\n", pali ? "true" : "false");
}

int main (void) {
    unsigned int x = B(10101);

    test(B(10101));
    test(0xFF0000ff);
    test(0xFF9E79ff);
    return 0;
}
