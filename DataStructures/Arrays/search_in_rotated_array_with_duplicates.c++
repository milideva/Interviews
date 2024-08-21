/*


81. Search in Rotated Sorted Array II

There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).

Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].

Given the array nums after the rotation and an integer target, return true if target is in nums, or false if it is not in nums.

You must decrease the overall operation steps as much as possible.

 

Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
 

Constraints:

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
nums is guaranteed to be rotated at some pivot.
-104 <= target <= 104

*/

#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {

        int l = 0, r = nums.size() - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (nums[mid] == target)
                return true;

            // If we can not determine sorted half due to duplicates
            if (nums[l] == nums[mid]) {
                l++;
                continue;
            }
            // If the left half is sorted
            if (nums[l] <= nums[mid]) {
                if (nums[l] <= target and target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                // If the right half is sorted
                if (nums[mid] < target and target <= nums[r]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return false;
    }
};

void testSearch() {
    Solution sol;

    // Test Case 1: Target found in rotated array
    vector<int> nums1 = {2, 5, 6, 0, 0, 1, 2};
    int target1 = 0;
    bool expected1 = true;
    assert(sol.search(nums1, target1) == expected1);
    cout << "Test Case 1 passed!" << endl;

    // Test Case 2: Target not found in rotated array
    vector<int> nums2 = {2, 5, 6, 0, 0, 1, 2};
    int target2 = 3;
    bool expected2 = false;
    assert(sol.search(nums2, target2) == expected2);
    cout << "Test Case 2 passed!" << endl;

    // Test Case 3: All elements are the same, target is present
    vector<int> nums3 = {1, 1, 1, 1, 1, 1, 1, 1};
    int target3 = 1;
    bool expected3 = true;
    assert(sol.search(nums3, target3) == expected3);
    cout << "Test Case 3 passed!" << endl;

    // Test Case 4: All elements are the same, target is absent
    vector<int> nums4 = {1, 1, 1, 1, 1, 1, 1, 1};
    int target4 = 2;
    bool expected4 = false;
    assert(sol.search(nums4, target4) == expected4);
    cout << "Test Case 4 passed!" << endl;

    // Test Case 5: Non-rotated array, target is present
    vector<int> nums5 = {1, 2, 3, 4, 5, 6, 7};
    int target5 = 4;
    bool expected5 = true;
    assert(sol.search(nums5, target5) == expected5);
    cout << "Test Case 5 passed!" << endl;

    // Test Case 6: Rotated array with duplicates, target is present
    vector<int> nums6 = {4, 5, 6, 6, 7, 0, 1, 2, 4, 4};
    int target6 = 0;
    bool expected6 = true;
    assert(sol.search(nums6, target6) == expected6);
    cout << "Test Case 6 passed!" << endl;

    // Test Case 7: Rotated array with duplicates, target is absent
    vector<int> nums7 = {4, 5, 6, 6, 7, 0, 1, 2, 4, 4};
    int target7 = 8;
    bool expected7 = false;
    assert(sol.search(nums7, target7) == expected7);
    cout << "Test Case 7 passed!" << endl;
}

int main() {
    testSearch();
    cout << "All test cases passed!" << endl;
    return 0;
}
