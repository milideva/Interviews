#include <stdio.h>
#include <limits.h>

#define CONST (5)

int main (void)
{

    int a, b, overflow;
    
    a = INT_MAX - CONST;
    b = CONST + 1;
    
    overflow = (a >= 0) ? (b > INT_MAX-a) : (b < INT_MIN-a);

    printf("a=%d b=%d, a+b %s overflow\n", a, b, overflow ? "will" : "will not");
    b = CONST;
    overflow = (a >= 0) ? (b > INT_MAX-a) : (b < INT_MIN-a);
    printf("a=%d b=%d, a+b %s overflow\n", a, b, overflow ? "will" : "will not");

    return 0;
}


