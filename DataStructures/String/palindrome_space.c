#include <stdio.h>
#include <string.h>

typedef int bool;
bool is_palindrome (char *str)
{

    if (!str)
        return 0;
    
    int len = strlen(str);
    int j = len -1;
    int i = 0;
    while (i<j) {
        if (str[i] == ' ') { 
            i++; 
            continue;
        }
        if (str[j] == ' ') {
            j--;
            continue;
        }
        if (str[i] != str[j])
            return 0;
        i++; j--;
    }
    return 1;
}

int main (void)
{
    char *test_pali1 = "amm  a";
    char *test_pali2 = "malay ala m";
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
