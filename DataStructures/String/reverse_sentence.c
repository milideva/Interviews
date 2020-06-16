#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char *reverse_sentence (char *str)
{
    if (!str)
        return NULL;
    int len = strlen(str);
    
    /* Original string may not be writable */
    char *ret = calloc(1, len + 1);

    if (!ret)
        return NULL;
    
    for (int i = 0; i < len; i++) {
        ret[i] = str[len-i-1];
    }
    ret[len] = '\0';

    return ret;
}

int main (void)
{
    char *str = "Devdatta Ajgaonkar Rocks!";
    printf("Original sentence: %s\n", str);
    char *ret = reverse_sentence(str);
    if (!ret) {
        return -1;
    }
    printf("Reversed sentence: %s\n", ret);
    free(ret);
    return 0;
}
