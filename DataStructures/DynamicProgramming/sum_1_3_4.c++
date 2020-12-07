/*

Solving a DP

1. Define subproblems
2. Write down the recurrence that relates subproblems
3. Recognize and solve the base cases

We are done.

Problem: given n, find the number of different ways to write n as the sum of 1, 3, 4

Example: forn= 5, the answer is 6
5   =  1 + 1 + 1 + 1 + 1
    =  1 + 1 + 3
    =  1 + 3 + 1
    =  3 + 1 + 1
    =  1 + 4
    =  4 + 1


Define subproblems–
    Let Dn be the number of ways to write n as the sum of 1, 3, 4

Find the recurrence–
    Consider one possible solution
    n = x1+x2+· · ·+xm
    – If xm= 1, the rest of the terms must sum to n−1
    – Thus, the number of sums that end with xm= 1 is equal to Dn−1
    – Take other cases into account (xm= 3,xm= 4)

Recurrence is then
    Dn = Dn−1 + Dn−3 + Dn−4

Solve the base cases
    – D0= 1
    – Dn= 0 for all negative n
    – Alternatively, can set: D0 = D1 = D2 = 1, and D3= 2
*/

#include <vector>
#include <iostream>

using namespace std;

int find_ways_sum_1_3_4 (int sum) {
    if (sum < 0) return 0;
    if (sum <= 2) return 1;
    vector <int> D(sum); // allocate size sum #elements
    D[0] = D[1] = D[2] = 1; D[3] = 2;
    for(int i = 4; i <= sum; i++)
        D[i] = D[i-1] + D[i-3] + D[i-4];

    return D[sum];
}

// The issue with above solution is size of array to memoize dp solution
// Use last few elements. space required = range ( d3, d2, d1, d0)
int find_ways_sum_1_3_4_optimized (int sum) {
    int d0, d1, d2, d3, di;
    d0 = d1 = d2 = 1; d3 = 2;
    if (sum < 0) return 0;
    if (sum < 3) return 1;
    if (sum == 3) return 2;

    for(int i = 4; i <= sum; i++) {
        di = d3 + d1 + d0;
        d0 = d1; d1 = d2; d2 = d3; d3 = di;
    }
    return di;
}

int main (void) {
    int sum = 7;
    int cnt = find_ways_sum_1_3_4(sum);
    cout << "sum: " << sum << " cnt:" << cnt << endl;

    cnt = find_ways_sum_1_3_4_optimized(sum);
    cout << "optimised sum: " << sum << " cnt:" << cnt << endl;
    return 0;
}
