/*

954. Array of Doubled Pairs

Given an integer array of even length arr, return true if it is
possible to reorder arr such that arr[2 * i + 1] = 2 * arr[2 * i] for
every 0 <= i < len(arr) / 2, or false otherwise.

Example 1:

Input: arr = [3,1,3,6]
Output: false
Example 2:

Input: arr = [2,1,2,6]
Output: false
Example 3:

Input: arr = [4,-2,2,-4]
Output: true
Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].
 
Constraints:

2 <= arr.length <= 3 * 104
arr.length is even.
-105 <= arr[i] <= 105

*/

#include <vector>
#include <iostream>
#include <set>

using namespace std;

class Solution {

public:
  bool canReorderDoubled(vector<int>& arr) {
    if (size(arr) % 2)
      return {};
    multiset <int> mst(arr.begin(), arr.end());
    auto sz = mst.size();
    for (auto i = 0; i < sz/2; i++) {
        auto elem = *mst.begin();
        mst.erase(mst.begin());
        auto toFind = 2 * elem;
        if (elem < 0) {
	          // {-5, -2} should be false, beware of truncation match
	          if (elem % 2) 
		            return false;
	          toFind = elem / 2;
        }
        auto it = mst.find(toFind);
        if (it == mst.end()) {
	          return false;
        }
        mst.erase(it);
    }
    return true;
  }
};

void printVec (vector <int> &vec, string str) {
  cout << str;
  for (auto i: vec) {
    cout << i << " ";
  }
  cout << endl;
}

int main () {

  vector <int> vec{4,-2,2,-4};
  printVec(vec, "Input: ");
  
  class Solution sol;
  auto ret = sol.canReorderDoubled(vec);
  cout << "Return: " <<	ret << endl;
  
  vec = {-5, -2};
  printVec(vec, "Input: ");
  ret = sol.canReorderDoubled(vec);
  cout << "Return: " << ret << endl;
  
  return 0;
}
