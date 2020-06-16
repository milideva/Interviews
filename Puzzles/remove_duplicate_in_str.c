#include <stdio.h>
#include <string.h>

enum bool_ {
    false, 
    true 
};
typedef enum bool_ bool;

int remove_duplicate_chars_from_string (char *str) {
    if (!str) return false;
    char ascii[256] = {};
    printf("input str:%s\n", str);
    int len = strlen(str);
    int i = 0;
    int j = 0;
    while (i < len) {
        
        char c = str[i];
        if (ascii[c]) {
            i++;
            continue;
        }
        ascii[c]++;
        str[j] = str[i];
        i++; 
        j++;
    }
    str[j] = '\0';
    printf("new str:%s\n", str);
    return true;

}

int main () {

    char arr[] = "devdatta";
    remove_duplicate_chars_from_string(arr);
    return 0;
}
