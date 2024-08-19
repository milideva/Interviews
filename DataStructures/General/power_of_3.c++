#include <iostream>

using namespace std;

/*

326. Power of Three

Given an integer n, return true if it is a power of three. Otherwise, return false.

An integer n is a power of three, if there exists an integer x such that n == 3x.


Example 1:

Input: n = 27
Output: true
Explanation: 27 = 33
Example 2:

Input: n = 0
Output: false
Explanation: There is no x where 3x = 0.
Example 3:

Input: n = -1
Output: false
Explanation: There is no x where 3x = (-1).
 

Constraints:

-231 <= n <= 231 - 1

*/

class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        while (n%3 == 0) {
            n /= 3;
        }

        return n == 1;
    }

    bool isPowerOfThreeRecursive (int n) {
        if (n <= 0) return false;
        if (n == 1) return true;
        if (n % 3) return false;
        return isPowerOfThreeRecursive(n/3);
    }
};

void test (int n) {
    Solution sol;
    cout << "n: "  << n << " powerOf3(): \t\t" << boolalpha << sol.isPowerOfThree(n) << endl;
    cout << "n: "  << n << " powerOf3Recursive(): \t" << boolalpha << sol.isPowerOfThreeRecursive(n) << endl << endl;

}

int main () {

    test(27);
    test(-1);
    test(1);
    test(0);

    return 0;
}