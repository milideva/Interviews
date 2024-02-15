/*
Given an array of integers nums and an integer target, return indices of the
two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not
use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]

 

Constraints:

    2 <= nums.length <= 103
    -109 <= nums[i] <= 109
    -109 <= target <= 109
    Only one valid answer exists.


*/

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
  vector <int> twoSum (vector <int>& nums, int target) {
    unordered_map <int, int> hashtable;
    
    for (int i = 0; i < nums.size(); i++) {
      if (hashtable.count(target - nums[i])) 
        return {i, hashtable[target-nums[i]]};
      hashtable[nums[i]] = i;
    }
    return {};
    
  }
};

void test (vector <int>& v, int target) {
  Solution sol;
  auto out = sol.twoSum(v, target);
  cout << "out = [" << out[0] << " , " << out[1] << "]" << endl;

  if (target != v[out[0]] + v[out[1]]) {
    cout << "target:" << target << " not matching with " << v[out[0]] << " + " << v[out[1]] << endl;
  } else {
    cout << "target:" << target << " matches with " << v[out[0]] << " + " << v[out[1]] << endl;
  }
}

int main () {
  vector <int> v1 = {2,7,11,15};
  int target = 9;
  test(v1, target);

  vector <int> v2 = {3,2,4};
  target = 6;
  test(v2, target);
  
  return 0;
}