#include <vector>
#include <iostream>

using namespace std;

/*
  Input sorted array of integers
  Output sorted array of squares of input array elements

  example :
  In = { -4, -3, 1, 2, 3 }
  Out = { 1, 4, 9, 9, 16 }

*/

class Solution {

public:
  vector <int> orderSquares (vector <int> &in) {
    vector <int> result;

    if (in.size() == 0)
      return result;

    // two pointer technique is needed to do this in O(n) instead of sorting in O(nlog(n))
    
    int left, right;
    right = 0;
    while (right < in.size() && in[right] < 0) {
      right++;
    }
    left = right - 1;
    
    while (left >= 0 && right < in.size()) {
      int lsq = in[left] * in[left];
      int rsq = in[right] * in[right];
      if (lsq < rsq) {
	result.push_back(lsq);
	left++;
	continue;
      }
      result.push_back(rsq);
      right++;
    }

    while (left >= 0) {
      int lsq = in[left] * in[left];
      result.push_back(lsq);
      left--;
    }
    while (right < in.size()) {
      int rsq =	in[right] * in[right];
      result.push_back(rsq);
    }
    
    return result;
  }
};


int main () {
  vector <int> in = { -4, -3, 0, 1, 2, 3 };
  class Solution sol;

  vector <int> res = sol.orderSquares(in);

  for (auto s : res) {
    cout << s << " " ;
  }
  cout << endl;
  return 0;
}
