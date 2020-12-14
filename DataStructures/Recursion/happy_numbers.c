#include <stdio.h>
#include <stdbool.h>

/*

A happy number is a number defined by the following process: Starting with any
positive integer, replace the number by the sum of the squares of its digits,
and repeat the process until the number equals 1 (where it will stay), or it
loops endlessly in a cycle which does not include 1. Those numbers for which
this process ends in 1 are happy numbers, while those that do not end in 1 are
unhappy numbers (or sad numbers)


If n is happy, then its sequence goes to 1. Otherwise, it ends in the cycle:

4, 16, 37, 58, 89, 145, 42, 20, 4, ... 

*/

int sum_squares (int n) {
    int sum = 0;
    int remain;

    while (n) {
        remain =  n%10;

        sum += (remain * remain);
        n /= 10;
    }
    
    return sum;
}

typedef enum e ret;

enum e { UNKNOWN, HAPPY, SAD };

ret is_sad (int sum) {

    if (sum==4||sum==16||sum==37||sum==58||sum==89||sum==145||sum==42||sum==20)
        return SAD;
    
    if (sum==1) return HAPPY;

    return UNKNOWN;
}

bool happy (int n) {

    int sum = sum_squares(n);
    ret r = is_sad(sum);

    if (r == SAD) {
        return false;
    }
    if (r== HAPPY) {
        return true;
    }

    return happy(sum);
}

int main()
{
    int i, cnt = 8;
    for (i = 1; cnt || !printf("\n"); i++)
        if (happy(i)) --cnt, printf("%d ", i);

    return 0;
}
