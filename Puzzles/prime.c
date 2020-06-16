#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

static void print_primes (unsigned n) {
    if (n < 4) {
        return;
    }

    int num = 4;
    int count = 2; /* 2 and 3 are primes */

    while (num < n) {
        int i;
        bool prime = true;

        /* actually till sqrt(num) */
        for (i = 2; i <= sqrt(num); i++) {
            printf(" num : %d sqrt:%d\n", num, (int) sqrt(num));
            if (num%i == 0) {
                prime = 0;
                break;
            }
        }
        if (prime) { 
            count++;
            printf(" Prime : %d\n", num);
        }

        num++;
    }
    printf("%s: n:%d primes:%d\n", __FUNCTION__, n, count);
}

/* Return the count of primes till n .
   The above algorithm is too slow for this problem.

   The sieve of Eratosthenes is one of the most efficient ways to find all
   primes smaller than n when n is smaller than 10 million

The program in the below link is much clearer than the one coded below.
https://www.geeksforgeeks.org/sieve-of-eratosthenes/

*/

static int num_primes (unsigned n) {
    bool is_prime[n];
    memset(is_prime, 0xFFff, n);
    unsigned count = 0;
    int i;
    is_prime[0] = is_prime[1] = false;

    /* sqrt is an optimization : using math lib,
       gcc -g -lm prime.c
       if it's not available, simply use n/2 .
    */

    for (i = 2; i < ceil(sqrt(n)); i++) {
        int num, mult = 2;
        /* Mark all multipliers of i as not prime */
        while ((num = i * mult) < n) {
            is_prime[num-1] = false; 
            mult++;
        }
    }

    for ( i = 0; i < n; i++) {
        /* If it's not cleaned up, then it must be a prime number */
        if (is_prime[i] == true) 
            count++;
    }
    printf("%s:: n:%d primes:%d\n", __FUNCTION__, n, count);
    return count;    
}

int main () {

    int n =134;
    print_primes(n);
    num_primes(n);

    num_primes(1000000);
    return 0;
}
