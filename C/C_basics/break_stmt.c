#include <stdio.h>

static void foo (int a, int b) {

    if (a) {

        if (b) {

            break;
            
        }
        printf("out of inner if\n");
    }
    printf("broke out of all ifs\n");
    
}
int main (void) {
    /* Break breaks out of nearest iteration or switch */
    /* This should not even compile */
    foo(5, 2);
    return 0;
}
