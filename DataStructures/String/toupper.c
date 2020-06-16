static int my_toupper (int c) {
    if ((c >= 'a') && (c <= 'z')) {
        c += 'A' - 'a';
    }
    return c;
}

static char * my_str_toupper (char *str) {
    if (!str)
        return str;

    int len = strlen(str);

    char *ret_str = calloc(1, len+1);

    int i = 0;
    while (i < len) {
        ret_str[i] = my_toupper(str[i]);
        i++;
    }
    ret_str[i] = '\0';
    return ret_str;
}

int main ()
{
    char *test = "devdatta";
    printf("orig:%s toupper:%s\n", test, 
            my_str_toupper(test));
    return 0;
}
