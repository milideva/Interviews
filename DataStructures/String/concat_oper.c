#include <stdio.h>

#define P(A) printf(#A"=%d \n",A)

int main()
{
    int x=2,y=3;
    P(x);
    P(y);
}
