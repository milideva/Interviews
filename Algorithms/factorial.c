#include <stdio.h>


unsigned int factorial (unsigned int a) {
    if (a == 1) return 1;
    return a * factorial(a-1);
}

#define MAX 50

unsigned long factorial_array[MAX];
/* Much faster - avoids recomputations in recursion, but needs extra memory */
unsigned int factorial_lookup (unsigned int a) {

    if (a > MAX) return 0;

    if (a == 1) {
        factorial_array[a] = 1;
    }
    if (factorial_array[a] == 0) {
        factorial_array[a] = a * factorial_lookup(a-1);
    }
    return factorial_array[a];
}

void test (unsigned int i) {

    printf("factorial(%d):%d\t", i, factorial(i));
    printf("factorial_lookup(%d):%d\n", i, factorial_lookup(i));
}

int main () {
    test(5);
    test(10);
    return 0;
}
