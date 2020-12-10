#include <iostream>
#include <vector>

/*

Given an array nums of n integers, are there elements a, b, c in nums such that
a + b + c = 0 

Find all unique triplets in the array which gives the sum of zero.

Notice that the solution set must not contain duplicate triplets.

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]

Example 2:

Input: nums = []
Output: []

Example 3:

Input: nums = [0]
Output: []

Constraints:

    0 <= nums.length <= 3000
    -105 <= nums[i] <= 105
*/

using namespace std;

<vector<vector <int>> 3sum (vector <int> &nums) {
  
  <vector<vector <int>> result;
  // This is with sorting allowed. If sorting not allowed, this method wont work
  sort(nums.begin(), nums.end());
  
  int len = nums.size();
 
  for (int i=0; i < len - 2; i++) {
    if (i > 0 && nums[i] == nums[i-1]) 
      continue;
    
    int l = i+1;
    int r = nums.end()-1;
    
    while (l <= r) {
      int s = nums[i] + nums[l] + nums[r];
      if (s == 0) {
        result.push_back(vector <int> { nums[i], nums[l], nums[r] });                   
        // handle duplicates
        while ( l < r && nums[l] == nums[l+1]) l++;
        while ( l < r && nums[r] == nums[r-1]) r--;
        l++; r--; 
        continue;
      } 
      if (s < 0) l++; 
      if (s > 0) r--;
    }
  }
  
}
