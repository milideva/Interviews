/* 
  Eliminate all 'b' and 'ac' in an array of characters, you have to replace them in-place, and you are only allowed to iterate over the char array once.

Examples:
abc -> ac
ac->''
react->rt

*/

char *eliminate_b_ac (char *str) {
    if (!str) return str;
    char *start, *ret_str = str;
    
    while (str) {
        if (*str == 'b') {
            int i, j, cnt; i = j = 0;
            while (str[i] && str[i]=='b') {
                i++;
            }
            cnt = i;
            while (cnt) {
                str[j] = str[i+j];
                if (str[j] == '\0') break;
                cnt--;
            }
        } else {

        }
        str++;
    }

    return ret_str;
}
