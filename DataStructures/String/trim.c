#include <stdio.h>
#include <stdlib.h>

/* Remove spaces */
unsigned trim (char *str) {
    char *dst = str;
    unsigned count = 0;

    if (!str) return count;
    while (*str) {
        if (*str != ' ') {
            *dst++ = *str;
        } else {
            count++;
        }
        str++;
    }
    *dst = '\0';
    return count;
}

int main () {
        char name[] = "Hello How Are you   ? ";
        int count = trim(name);
        printf("count:%d trimmed:%s\n", count, name);
}
