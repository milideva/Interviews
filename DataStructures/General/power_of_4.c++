#include <iostream>

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
