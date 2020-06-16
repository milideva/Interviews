#include <stdio.h>

typedef int bool;
static bool 
is_power_of_two (unsigned int v) {
    return v && !(v & (v - 1));
}

int main (void) {
    unsigned int a = 11;
    printf("%d is %s power of two\n", a, is_power_of_two(a) ? "" : "not"); 
    a = 16;
    printf("%d is %s power of two\n", a, is_power_of_two(a) ? "" : "not");
    return 0;
}
