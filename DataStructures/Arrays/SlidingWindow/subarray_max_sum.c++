#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

/*

53. Maximum Subarray
Given an integer array nums, find the subarray with the largest sum, and return its sum.

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
Example 2:

Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.
Example 3:

Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.

Intuition
For any sub-array ending at an index i, we have 2 options

Sub-array has just one element. (If the contribution of the subarray ending at i-1 < 0, adding that to the current element will only decrease the current sub-array's sum, and hence it will not help to find the max-subarray sum.)
Sub-array has more than one element. (If the contribution fo the subarray ending at i-1>0, adding that subarray to the current element will increase the current sub-array's sum. It doesnt matter the individual elements before i, we are only interested in the contribution of the previous sub-array as a whole. )
*/


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = nums[0];
        int maxSum = nums[0];

        // Start the loop from the second element
        for (int i = 1; i < nums.size(); i++) {
            // Either add the current element to the current sum or start fresh from the current element
            sum = max(nums[i], sum + nums[i]);
            // Update maxSum if currentSum is greater
            maxSum = max(maxSum, sum);
        }
        return maxSum;
    }
};

void runTestCases_maxSubArray() {
    Solution solution;

    // Test Case 1
    vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    assert(solution.maxSubArray(nums1) == 6);

    // Test Case 2
    vector<int> nums2 = {1};
    assert(solution.maxSubArray(nums2) == 1);

    // Test Case 3
    vector<int> nums3 = {5, 4, -1, 7, 8};
    assert(solution.maxSubArray(nums3) == 23);

    // Additional Test Case 4: All negative numbers
    vector<int> nums4 = {-3, -2, -1, -4};
    assert(solution.maxSubArray(nums4) == -1);

    // Additional Test Case 5: Single large negative number
    vector<int> nums5 = {-1};
    assert(solution.maxSubArray(nums5) == -1);

    // Additional Test Case 6: Mix of positive and negative numbers
    vector<int> nums6 = {-1, 2, 3, -5, 4, -2, 3, -1, 2};
    assert(solution.maxSubArray(nums6) == 6);

    // Additional Test Case 7: Large input with all positive numbers
    vector<int> nums7(1000, 1); // Array of 1000 ones
    assert(solution.maxSubArray(nums7) == 1000);

    // Additional Test Case 8: Array of size 0 (not expected per problem constraints, but handling gracefully)
    vector<int> nums8 = {}; // This case can be undefined based on problem constraints.
    // Here we might skip it or assume input size is always >= 1

    cout << "All test cases passed!" << endl;
}

/*

 Given an array of positive integers nums and an integer k, 
 find the length of the longest sub-array whose sum is less than or equal to k.
*/


/*

The sliding windows algorithm
The idea behind a sliding window is to consider only valid subarrays. Recall that a subarray can be defined by a left bound (the index of the first element) and a right bound (the index of the last element). In sliding window, we maintain two variables left and right, which at any given time represent the current subarray under consideration.

Initially, we have left = right = 0, which means that the first subarray we look at is just the first element of the array on its own. We want to expand the size of our "window", and we do that by incrementing right. When we increment right, this is like "adding" a new element to our window.

But what if after adding a new element, the subarray becomes invalid? We need to "remove" some elements from our window until it becomes valid again. To "remove" elements, we can increment left, which shrinks our window.

As we add and remove elements, we are "sliding" our window along the input from left to right. The window's size is constantly changing - it grows as large as it can until it's invalid, and then it shrinks. However, it always slides along to the right, until we reach the end of the input.

*/
int sumLongestSubArrayMaxK (vector <int> &vec, int k) {
    int left, right, sum, ans;

    left = sum = ans = 0;
    for (right = 0; right < vec.size(); right++) {
        sum += vec[right];

        while (sum > k) {
            // reduce the window by moving left to right by 1.
            left++;
            sum -= vec[left];
        }
        ans = max(ans, right - left + 1);
    }

    return ans;
}

void printVector(const std::vector<int>& nums) {
    for (const int& num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void test (void) {
    vector <int> nums = {3, 1, 2, 7, 4, 2, 1, 1, 5};
    int k = 8;

    int ans = sumLongestSubArrayMaxK(nums, k);

    printVector(nums);
    cout << "k = " << k << " sumLongestSubArrayMaxK: " << ans << endl;
}

int main() {
    test();
    runTestCases_maxSubArray();
}