/*

2007. Find Original Array From Doubled Array

An integer array original is transformed into a doubled array changed
by appending twice the value of every element in original, and then
randomly shuffling the resulting array.

Given an array changed, return original if changed is a doubled
array. If changed is not a doubled array, return an empty array. The
elements in original may be returned in any order.

Example 1:

Input: changed = [1,3,4,2,6,8]
Output: [1,3,4]
Explanation: One possible original array could be [1,3,4]:
- Twice the value of 1 is 1 * 2 = 2.
- Twice the value of 3 is 3 * 2 = 6.
- Twice the value of 4 is 4 * 2 = 8.
Other original arrays could be [4,3,1] or [3,1,4].
Example 2:

Input: changed = [6,3,0,1]
Output: []
Explanation: changed is not a doubled array.
Example 3:

Input: changed = [1]
Output: []
Explanation: changed is not a doubled array.
 

Constraints:

1 <= changed.length <= 105
0 <= changed[i] <= 105

*/

#include <vector>
#include <iostream>
#include <set>

using namespace std;

class Solution {
    vector <int> result;
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        if (size(changed) % 2) 
            return {};
	      result.clear();
        multiset <int> mst(changed.begin(), changed.end());
        auto sz = mst.size();
        for (auto i = 0; i < sz/2; i++) {
            auto elem = *mst.begin();
            mst.erase(mst.begin());
            auto it = mst.find(elem * elem);
            if (it == mst.end()) {
                return {};
            }
            result.push_back(elem);
            mst.erase(it);
        }
        return result;
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

  vector <int> vec {1,1,4,2,-3,9};
  printVec(vec, "Input: ");
  
  class Solution sol;
  auto result = sol.findOriginalArray(vec);
  printVec(result, "Result: ");

  vec = {9, -3, 0, 0, -1, 1};
  printVec(vec, "Input: ");
  result = sol.findOriginalArray(vec);
  printVec(result, "Result: ");

  return 0;
}
