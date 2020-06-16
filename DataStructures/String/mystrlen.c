/* strlen does not account for \0 */
/* Whereas sizeof DOES ! */
int mystrlen (char *str)
{
    int len = 0;
    if (!str)
        return len;

    while (*str++) 
        len++;
    return len;
}

int main () {
        char *str = "devdatta";
        printf("string:%s len:%d\n", str, mystrlen(str));
        return 0;
}
