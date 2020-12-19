#include <stdbool.h>

bool number_palindrome (unsigned int num) {

    unsigned int orig_num = num;
    unsigned int reverse, digit;

    reverse = 0;

    while (num) {
        digit = num % 10;
        reverse = reverse * 10 + digit;
        num = num / 10;
    }

    bool ret;

    ret = (reverse && (reverse==orig_num));
        
    printf("%d is %s a palindrome.\n", 
           orig_num, ret ? "" : "not");
    return ret;
}

int main () {
    int num = 1234321;
    bool ret = number_palindrome(num);

    num = 12343;
    ret = number_palindrome(num);

    return 0;
}
