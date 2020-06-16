#include <stdio.h>
#include <string.h>

typedef int bool; /* For C99 it's #include <bool.h> */

bool is_palindrome (char *str)
{

    if (!str)
        return 0;
    
    int len = strlen(str);

    for (int i = 0; i < len/2 ; i++) {
        if (str[i] != str[len-i-1])
            return 0;
    }
    return 1;
}

int main (void)
{
    char *test_pali1 = "amma";
    char *test_pali2 = "malayalam";
    char *test_pali3 = "devdatta";
    
    int ret;

    ret = is_palindrome(test_pali1);
    printf("%s is %s a palindrome\n", test_pali1, ret ? "" : "not");

    ret = is_palindrome(test_pali2);
    printf("%s is %s a palindrome\n", test_pali2, ret ? "" : "not");

    ret = is_palindrome(test_pali3);
    printf("%s is %s a palindrome\n", test_pali3, ret ? "" : "not");
    
    return 0;
}
