#include <string.h>
#include <stdio.h>

/* Please read wiki on fibonacci.

AKA 
Male Bee ancestry problem.
Rabit population problem.

You are climbing a stair case. Each time you can either make 1 step or 2
steps. The staircase has n steps. In how many distinct ways can you climb
the staircase ?
*/

/*
   0 0
   1 1
   2 1
   3 2
   4 3
   5 5
   6 8
   7 13
   8 21
   9 34
   10 55
   11 89
   12 144
   13 233
   14 377
 */
int fibonacci (int num) {
    if (num < 0)
        return -1;
    if (num < 2) return num;

    return fibonacci(num-1) + fibonacci(num-2);
}
    
/*

Dynamic Programming is an algorithmic paradigm that solves a given complex
problem by breaking it into subproblems and stores the results of subproblems
to avoid computing the same results again. Following are the two main
properties of a problem that suggest that the given problem can be solved
using Dynamic programming.

1) Overlapping Subproblems
2) Optimal Substructure

*/

/* Memoization based. Dynamic programming.
 */

unsigned int fibonacci_lookup (unsigned int n) {
    unsigned int lookup[n];
    unsigned int fibonacci = 0;
   
    if (n < 2) return n;

    memset(lookup, 0, sizeof lookup);
    unsigned int input = 2;

    lookup[0] = 0;
    lookup[1] = 1;

    while (input <= n) {
        lookup[input] = lookup[input-1] + lookup[input-2];
        input++;
    }

    return lookup[n];
}

/* Without extra space, without recursion */

unsigned int fibonacci_optimal (unsigned int n) {
    unsigned int back1, back2, i, sum;

    if (n<2) return n;
    back1 = 0;
    back2 = 1;
    i = 2;
    while (i++ <= n){
        sum = back1 + back2;
        back1 = back2;
        back2 = sum;
    }
    return sum;
}

static void test (unsigned int i) {

    printf("fibonacci(%d):%d\t", i, fibonacci(i));
    printf("fibonacci_lookup(%d):%d     ", i, fibonacci_lookup(i));
    printf("fibonacci_optimal(%d):%d\n", i, fibonacci_optimal(i));
}

int main () {

    test(5);
    test(11);
    test(14);

    return 0;
}
