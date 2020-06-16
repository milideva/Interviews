#include <stdio.h>
#include <string.h>

static void reverse_a_word (char *start, char *end) {
    if (!start || !end) return;
    while (start < end) {
        char temp = *start; 
        *start++ = *end; 
        *end-- = temp;
    }
}

static void get_a_word_size (char *str, int *size) {
    if (!str || !size) return;
    *size = 0;

    while (*str != '\0') {
        if (*str == ' ') {
            break;
        }
        str++; 
        (*size)++; 
    }
    return;
}

static void reverse_string (char *str)
{
    if (!str)
        return;
    
    reverse_a_word(str, str + strlen(str)-1);
}

static void reverse_words_in_sentence (char *str) {

    if (!str) return;
    char *start, *end;
    start = end = str;
    int len;

    /* "a bc def" becomes "fed cb a" */
    reverse_string(str);

    /* Reverse individual words now */

    while (*str != '\0') {
        len = 0;
        get_a_word_size(str, &len); // get current word size

        reverse_a_word(str, str+len-1); // reverse current word
        str = str + len; // advance to end of this word
        while (*str == ' ') str++; //eat up all spaces
    }
}

int main () {
    char test_str[] = "I am a cool dude!";
    printf("Input string:%s\n", test_str);
    reverse_words_in_sentence(test_str);
    printf("Output sentence:%s\n", test_str);
    return 0;
}
