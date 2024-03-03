/*

75. Sort Colors

Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

Example 1:

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]
 

Constraints:

n == nums.length
1 <= n <= 300
nums[i] is either 0, 1, or 2.


*/

#include <vector>
#include <iostream>
#include <array>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        const int MAX_COLORS = 3;
        array <int, MAX_COLORS> arr = {0};

        for (auto n : nums) {
            if (n > MAX_COLORS - 1) return;
            arr[n]++;
        }
        int index = 0;
        for (int i = 0; i < MAX_COLORS; i++) {
            int sz = arr[i];
            while (sz) {
                nums[index] = i;
                index++;
                sz--;
            }
        }
        return;
    }
};


void test(vector<int> nums) {
    Solution sol;
    sol.sortColors(nums);
    for (auto n : nums) {
        cout << n << " ";
    }
    cout << endl;
}

int main() {
    test({2,0,2,1,1,0});
    test({2,0,1});
    return 0;
}