#include <vector>
#include <iostream>

using namespace std;

/*
33. Search in Rotated Sorted Array

There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an
unknown pivot index k (1 <= k < nums.length) such that the resulting
array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ...,
nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated
at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer
target, return the index of target if it is in nums, or -1 if it is
not in nums.

You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1

*/


class Solution {
  public:
    int search (vector<int>& nums, int target) {
        int left = 0;
        int right = size(nums) - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2 ;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[mid] < nums[left]) {
                // rotated start is in left half
                if (target > nums[mid] && target <= nums[right]) {
                    // target is in right half
                    left = mid + 1;
                } else {
                    // target is in left half, repeat binary search
                    right = mid - 1;
                }
            } else {
                // rotated start is in the right half
                if (target < nums[mid] && target >= nums[left]) {
                    // target is in left half, repeat binary search
                    right = mid - 1;
                } else {
                    // target is in right half
                    left = mid + 1;
                }
                
            }
        }
        return -1;
    }
};

int main () {
  Solution sol;
  vector <int> nums = {4,5,6,7,0,1,2};
  auto target = 0;
  auto i = sol.search(nums, target);

  cout << "searching for " << target << " Index: " << i << endl;

  nums = {4,5,6,7,0,1,2};
  target = 3;

  i = sol.search(nums, target);

  cout << "searching for " << target << " Index: " << i	<< endl;

  return 0;
}
