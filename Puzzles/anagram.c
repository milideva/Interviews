#include <stdbool.h>
/*
Anagram : rearranging the letters of a word or phrase to produce a new word or phrase, Mary => Army
*/
bool anagram (char *str1, char *str2) {
    int len1, len2;
    if (!str1 || !str2) return false;
    
    len1 = strlen(str1);
    len2 = strlen(str2);

    if (len1 != len2) return false;

    int count[256];
    memset(count, 0, sizeof(count));

    char *s1, *s2;
    s1 = str1; s2 = str2;

    while (*str1) {
        count[*str1]++;
        str1++;
    }
    while (*str2) {
        count[*str2]--;
        str2++;
    }

    int i = 256;
    while (i) {
        if (count[i]) return false;
        i--;
    }
    printf("%s::true: str1:%s str2:%s\n", __FUNCTION__, s1, s2);
    return true;

}
    
int main () {
    char str1[] = "Devdatta";
    char str2[] = "dattaDev";

    bool ret = anagram(str1, str2);
}
