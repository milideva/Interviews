
/* 
   Implement an algorithm to determine if a string has all unique characters
   What if you can not use additional data structures?
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>


bool unique_chars (unsigned char *str) {
    char char_set[256] = {0};
    if (!str) return false;
    
    while (*str != '\0') {
        if (char_set[*str]) return false;
        char_set[*str] = 1;
        str++;
    }
    return true;
}

/* Remove duplicate characters in-place.
 * Assumptions : 
 1. input string is RW memory and is modified and returned.
 2. Case-sensitive characters.
*/

void remove_duplicates (unsigned char *str) {
    unsigned char ascii[256] = { 0 };
    if (!str) return;
    
    unsigned char *dst, *src;
    src = dst = str;

    while (*src != '\0') {
        if (ascii[*src]) {
            ascii[*src]++; src++;
            continue;
        }
        ascii[*src]++;
        *dst++ = *src++;
    }
    *dst = '\0';
}

int main (void) {
    unsigned char str[] = "ABCd";
    bool ret = unique_chars(str);
    printf("str:%s unique_chars:%s\n", str, ret ? "yes" : "false");

    unsigned char str1[] = "AAAABBBBccab";
    ret = unique_chars(str1);
    printf("str:%s unique_chars:%s\n", str1, ret ? "yes" : "false");

    unsigned char str2[] = "ABCdDabb";
    ret = unique_chars(str2);
    printf("str:%s unique_chars:%s\n", str2, ret ? "yes" : "false");

    unsigned char str3[] = "Devdatta";
    ret = unique_chars(str3);
    printf("str:%s unique_chars:%s\n", str3, ret ? "yes" : "false");

    unsigned char name[] = "devdatta";

    remove_duplicates(name);
    printf("remove_duplicates name:%s\n", name);

    remove_duplicates(str1);
    printf("remove_duplicates name:%s\n", str1);

    
    return 0;
}
    
