#include <stdio.h>

static void reverse_a_word (char *start, char *end) {
    if (!start || !end) return;
    while (start < end) {
        char temp = *start; 
        *start++ = *end; 
        *end-- = temp;
    }
}

static void reverse_sentence (char *str) {

    if (!str) return;
    char *start, *end;
    start = end = str;
    
    while (*str) {
        if (*str == ' ') {
            reverse_a_word(start, str-1);
            while (*str == ' ') {
                str++;
            }
            start = str; continue;
        }
        str++;
    }

    reverse_a_word(start, str-1);
}

int main () {
    char test_str[] = "Cisco rocks!! Cat Meow meows!";
    printf("Orig test_str:%s\n", test_str);
    reverse_sentence(test_str);
    printf("New  test_str:%s\n", test_str);
    return 0;
}
