#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/* 
3sum closest

Given an integer array nums of length n and an integer target, find
three integers in nums such that the sum is closest to target.

Return the sum of the three integers.

You may assume that each input would have exactly one solution.

Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
Example 2:

Input: nums = [0,0,0], target = 1
Output: 0

*/

// Time:  O(n^2)
// Space: O(∣ans∣)

class Solution {
    int closestSum = 1000000000;
public:
    int threeSumClosest(vector<int>& nums, int target) {
    
        sort(begin(nums), end(nums));
            
        for (auto i = 0; i < size(nums) - 2; i++) {
            int left = i+1;
            int right = size(nums) - 1;
            
            while (left < right) {
                auto sum = nums[i] + nums[left] + nums[right];
                if (abs(sum - target) == 0) {
                    return sum;
                }
                
                if (abs(target - sum) < abs(target - closestSum)) {
                    closestSum = sum;
                }
                if (sum > target) {
                    right--;
                }
                if (sum < target) {
                    left++;
                }
            }
        }
        
        return closestSum;
    }
};

int main () {
  vector <int> nums = { -4, -3 , 0,  3, 10, 20 };
  vector <int> nums2 = { -2 , 0, 1, 3 };
  class Solution sol;
  auto target = 0;
  auto ans = sol.threeSumClosest(nums, target);

  cout << "For nums: answer:" <<  ans << " target:" << target << endl;

  target = -3;
  ans = sol.threeSumClosest(nums2, target);
  cout << "For nums2 : answer:" <<  ans << " target:" << target << endl;
  return 0;
}
