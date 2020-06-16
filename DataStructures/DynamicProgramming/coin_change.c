/*
Given a set of coin values coins = {c1, c2,..., ck} and a target sum of money n, our task
is to form the sum n using as few coins as possible.

The dynamic programming algorithm is based on a recursive function that goes
through all possibilities how to form the sum, like a brute force algorithm.
However, the dynamic programming algorithm is efficient because it uses
memoization and calculates the answer to each subproblem only once.

*/

#include <stdio.h>
#include <limits.h>

int value[100];
int coin[] = {1, 5, 10, 25, 50, 100};

int min (int a, int b) {
    if (a < b) return a;
    return b;
}

int solve (int x) {
    if (x <= 0) return 0;

    if (value[x]) return value[x];
    int best = INT_MAX;
    int num_coins = sizeof coin / sizeof coin[0];

    for (int i = 0; i < num_coins; i++) {
        int c = coin[i];
        if ((x-c) <= 0) continue; 
        
        best = min(best, solve(x-c)+1);
    }
    value[x] = best;
    return best;
}

void init (void) {
    int num_coins = sizeof coin / sizeof coin[0];
    for (int i = 0; i < num_coins; i++) {
        int c = coin[i];
        value[c] = 1;
    }
}

int main () {
    int sum = 99;
    init();
    int num = solve(sum);
    printf("For Sum %d #coins:%d \n", sum, num);
    return 0;
}
