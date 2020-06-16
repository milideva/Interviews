int ic_strcmp (char *s1, char *s2) {

    char c1, c2;

    while (s1 && s2) {

        if (*s1 == *s2) {
            if (*s1 == '\0') 
                break;
            s1++; s2++; 
            continue;
        }
        
        c1 = *s1; 
        c2 = *s2;
        if ( ((c1-c2) == ('a'-'A')) || ((c1-c2) == ('A'-'a')) ) {
           s1++; s2++; 
           continue; 
        }
        return c1-c2;
    }
    return 0;
}

int main (void) {
    char *str1 = "Devdatta";
    char *str2 = "deVdAttA";

    int ret = ic_strcmp(str1, str2);
    printf("str1:%s " "%s " "str2:%s\n", str1, ret ? "!=" : "==", str2);
    return 0;
}
