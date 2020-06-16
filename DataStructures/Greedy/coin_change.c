/*
Given a set of coin values coins = {c1, c2,..., ck} and a target sum of money n, our task
is to form the sum n using as few coins as possible.


In the general case, the coin set can contain any coins and the greedy algorithm
does not necessarily produce an optimal solution.

We can prove that a greedy algorithm does not work by showing a counterexample
where the algorithm gives a wrong answer. In this problem we can easily
find a counterexample: if the coins are {1,3,4} and the target sum is 6, the greedy
algorithm produces the solution 4+1+1 while the optimal solution is 3+3.

It is not known if the general coin problem can be solved using any greedy
algorithm.

However, in some cases, the general problem can be efficiently solved using a
dynamic programming algorithm that always gives the correct answer.

*/

#include <stdio.h>
#include <limits.h>

int value[100];
int coin[] = {1, 5, 10, 25, 50, 100};


// A simple greedy algorithm to the problem always selects the largest possible coin

int solve (int x) {
    if (x <= 0) return 0;

    int num_coins = sizeof coin / sizeof coin[0];
    int result_coins = 0;
    for (int i = num_coins - 1; i >= 0; i--) {
        int c = coin[i];
        result_coins += x/c;
        x = x % c;
    }

    return result_coins;
}

int main () {
    int sum = 99;
    int num = solve(sum);
    printf("For Sum %d #coins:%d \n", sum, num);
    return 0;
}
