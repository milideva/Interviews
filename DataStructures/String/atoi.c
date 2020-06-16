#include <stdio.h>

int myatoi (char *str)
{
    if (!str)
        return 0;
    int val = 0;
    while (*str) {
        int a = *str - '0';
        if ((a >= 0) && (a <= 9)) {
            /* It will ignore all other characters */    
            val = val * 10 + a;
        } 
        str++;
    }
    return val;
}

int main (void) 
{
        char *test = "12"; // @ + 1456 !";

        int a = myatoi(test);
        
        printf("myatoi(%s) = %d\n", test, a);
        
        return 0;

}
