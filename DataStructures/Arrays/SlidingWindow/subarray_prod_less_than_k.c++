#include <vector>
#include <iostream>

using namespace std;

/*
713. Subarray Product Less Than K.

Given an array of positive integers nums and an integer k, return the number of subarrays where the product of all the elements in the subarray is strictly less than k.

For example, given the input nums = [10, 5, 2, 6], k = 100, the answer is 8. The subarrays with products less than k are:

[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
*/

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) {
            return 0;
        }

        int ans = 0, left = 0, prod = 1;

        // The constraint metric is: product of the window. The numeric restriction is < k. 
        // The condition that makes a window invalid is prod >= k.
        for (int right = 0; right < nums.size(); right++) {
            prod *= nums[right];

            // Add elements to the window with prod *= nums[right]. Remove them with prod /= nums[left].


            while (prod >= k) {
                prod /= nums[left];
                left++;
            }
            
            // If we fix the right bound, how many values can left take? r - l + 1
            ans += right - left + 1;
        }
        
        return ans;
    }
};

void testNumSubarrayProductLessThanK() {
    Solution sol;
    int passed = 0;
    int failed = 0;

    // Test case 1
    vector<int> nums1 = {10, 5, 2, 6};
    int k1 = 100;
    int expected1 = 8;
    int result1 = sol.numSubarrayProductLessThanK(nums1, k1);
    cout << "Test case 1: expected = " << expected1 << ", got = " << result1;
    if (result1 == expected1) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 2
    vector<int> nums2 = {1, 2, 3};
    int k2 = 0;
    int expected2 = 0;
    int result2 = sol.numSubarrayProductLessThanK(nums2, k2);
    cout << "Test case 2: expected = " << expected2 << ", got = " << result2;
    if (result2 == expected2) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 3
    vector<int> nums3 = {1, 2, 3};
    int k3 = 1;
    int expected3 = 0;
    int result3 = sol.numSubarrayProductLessThanK(nums3, k3);
    cout << "Test case 3: expected = " << expected3 << ", got = " << result3;
    if (result3 == expected3) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 4
    vector<int> nums4 = {1, 1, 1};
    int k4 = 2;
    int expected4 = 6;
    int result4 = sol.numSubarrayProductLessThanK(nums4, k4);
    cout << "Test case 4: expected = " << expected4 << ", got = " << result4;
    if (result4 == expected4) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 5
    vector<int> nums5 = {10, 9, 10, 4, 2};
    int k5 = 100;
    int expected5 = 10;  // Corrected expected value
    int result5 = sol.numSubarrayProductLessThanK(nums5, k5);
    cout << "Test case 5: expected = " << expected5 << ", got = " << result5;
    if (result5 == expected5) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 6: Edge case with empty array
    vector<int> nums6 = {};
    int k6 = 100;
    int expected6 = 0;
    int result6 = sol.numSubarrayProductLessThanK(nums6, k6);
    cout << "Test case 6: expected = " << expected6 << ", got = " << result6;
    if (result6 == expected6) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Test case 7: Large numbers
    vector<int> nums7 = {10, 5, 2, 6};
    int k7 = 10;
    int expected7 = 3;
    int result7 = sol.numSubarrayProductLessThanK(nums7, k7);
    cout << "Test case 7: expected = " << expected7 << ", got = " << result7;
    if (result7 == expected7) {
        cout << " -> passed!" << endl;
        passed++;
    } else {
        cout << " -> failed!" << endl;
        failed++;
    }

    // Summary
    cout << "Summary: " << passed << " tests passed, " << failed << " tests failed." << endl;
}

int main() {
    testNumSubarrayProductLessThanK();
    return 0;
}