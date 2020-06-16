#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char *my_strcat (char *orig, const char* append) {
    int total_len = strlen(orig) + strlen(append) + 1;
    char *final_str = calloc(1, total_len);
    strncpy(final_str, orig, strlen(orig));
    strncat(final_str, append, strlen(append));
    printf("%s: final_str:%s\n", __FUNCTION__, final_str);
    return final_str;
}
int main (void) {
    char *str = "devdatta";
    int len = strlen(str);

    char buf[256] = {0}; // Init the buffer
    char *msg = "Have a great day! ";
    snprintf(buf, sizeof(buf), "%s",  msg);
        
    printf("buf is :%s:len:%d\n", buf, strlen(buf));
    printf("append str :%s\n", str);

    free(my_strcat(buf, str));
    return 0;
}
