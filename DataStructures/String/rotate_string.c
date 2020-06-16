#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

static void reverse_string (char *str, int start, int end) {
    if (!str)
        return;

    assert(start >= 0);
    assert((end > 0) && (end < strlen(str)));
    assert(start < end);
    
    char *from = str + start;
    char *to = str + end;

    printf("Original string:%s start:%d, end:%d\n", str, start, end);

    while (from < to) {
        char temp = *from;
        *from++ = *to;
        *to-- = temp;
    }

    printf("Reversed string:%s\n", str);

}

static void rotate_left_string (char *str, int rotate) {
    assert(str);
    int len = strlen(str);
    printf("%s: str:%s len:%lu rotate:%d\n", __FUNCTION__, str, strlen(str), rotate);
    assert(rotate <= len);
    if (rotate == len) return;
    
    reverse_string(str, 0, rotate-1);
    reverse_string(str, rotate, len-1);
    reverse_string(str, 0, len-1);
    
    printf("%s: str:%s rotated left by %d\n", __FUNCTION__, str, rotate);
}

static bool rotate_right_string (char *str, int rotate) {
    if (!str || rotate < 0) return false;
    int len = strlen(str);

    if ((rotate == len) || (rotate == 0)) return true;

    if (rotate > len) rotate = rotate % len;

    printf("%s: str:%s len:%lu rotate:%d\n", __FUNCTION__, str, strlen(str), rotate);
    reverse_string(str, 0, len-1-rotate);
    reverse_string(str, len-rotate, len-1);
    reverse_string(str, 0, len-1);

    printf("%s: str:%s rotated right by %d\n", __FUNCTION__, str, rotate);
    return true;
}

int main (void) {

	char str[] = "1234567890abcdefgh";
    rotate_left_string(str, 4);
    rotate_right_string(str, 4);
	return 0;
}


