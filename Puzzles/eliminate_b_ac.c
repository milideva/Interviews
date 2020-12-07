/* 
  Eliminate all 'b' and 'ac' in an array of characters, you have to replace them in-place, and you are only allowed to iterate over the char array once.

Examples:
abc -> ac
ac->''
react->ret

*/
#include <stdio.h>

void eliminate_b_ac (char *str) {
    char *rd, *wr;
    if (!str) return;

    rd = wr = str;
    while (*rd != '\0') {
        if (*rd == 'b') {
            rd++; continue;
        }
        if (*rd == 'c' && *(wr-1) == 'a' && wr!=str) {
            rd++;
            wr--;
            continue;
        } 
        *wr++ = *rd++;
    }
    *wr = '\0';
}

int main() {
    char str[] = "abc";
    eliminate_b_ac(str);
    printf("%s\n", str);


    char str2[] = "react";
    eliminate_b_ac(str2);
    printf("%s\n", str2);
    return 0; 
}
