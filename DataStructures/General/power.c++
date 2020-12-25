/*
Implement pow(x, n), which calculates x raised to the power n (i.e. xn).

 

Example 1:

Input: x = 2.00000, n = 10
Output: 1024.00000

Example 2:

Input: x = 2.10000, n = 3
Output: 9.26100

Example 3:

Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25

 

Constraints:

    -100.0 < x < 100.0
    -231 <= n <= 231-1
    -104 <= xn <= 104


*/

/*

Fast Power Algorithm Recursive

Intuition

Assuming we have got the result of x^ n, how can we get x ^ {2 * n}? 

Obviously we do not need to multiply x for another n times. Using the formula
(x^n)^2 = x ^ {2 * n}, we can get x ^ {2 * n} at the cost of only one
computation. Using this optimization, we can reduce the time complexity of our
algorithm.

Algorithm

Assume we have got the result of x ^ {n / 2}, and now we want to get the
result of x ^ n. Let A be result of x ^ {n / 2}, we can talk about
x ^ n based on the parity of n respectively. 

If n is even, we can use the formula (x ^ n) ^ 2 = x ^ {2 *n}
to get x ^ n = A * A.


If n is odd, then A ∗ A = x^ {n−1} 
Intuitively, We need to multiply another x to the result,
so x ^ n = A * A * x. 

This approach can be easily implemented using recursion. We call this method
"Fast Power", because we only need at most O(log⁡n) computations to get x ^ n.

*/

#include <iostream>
using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        if (!x) return x;
        long long N = n;
        
        if (!n) return 1.0;
        if (n < 0) {
            N = -N;
            x = 1/x;
        }
        double y = 1.0;
        while ( N > 1) {
            if ( N % 2 == 0) { // n is even
                x = x * x;
                N = N / 2;
            } else {
                y = x * y;
                x = x * x;
                N = (N - 1) / 2;
            }
        }
        return x * y;
    }
};

int main () {
  class Solution sol;

  double x = 2;
  int n = 10;
  double p = sol.myPow(x, n);
  cout << "pow(x,n) x:" << x << " n:" << n << " = " << p << endl;
  return 0;
}
