#include <iostream>

/*
    342. Power of Four

Given an integer n, return true if it is a power of four. Otherwise, return false.

An integer n is a power of four, if there exists an integer x such that n == 4x.

    Example 1:

Input: n = 16
Output: true
Example 2:

Input: n = 5
Output: false
Example 3:

Input: n = 1
Output: true
 

Constraints:

-231 <= n <= 231 - 1
*/
    
using namespace std;

class Solution {
public:
    bool isPowerOfFour(int n) {
        if (n <= 0) return false;
        if (n == 1) return true;
        if (n % 4) return false;
        return isPowerOfFour(n/4);
    }
};

void test (int n) {
  Solution sol;
  cout << "n: " << n << boolalpha << " isPowerOfFour: " << sol.isPowerOfFour(n) << endl;
}

int main () {
  int n = 16;
  test(n);
  n = 5;
  test(n);
  n = 1;
  test(n);
  
  return 0;
}
