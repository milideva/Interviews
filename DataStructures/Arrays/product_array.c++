/*
    238. Product of Array Except Self

    Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

    The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

    You must write an algorithm that runs in O(n) time and without using the division operation.

    Example 1:
    Input: nums = [1,2,3,4]
    Output: [24,12,8,6]

    Example 2:
    Input: nums = [-1,1,0,-3,3]
    Output: [0,0,9,0,0]


    Constraints:
    2 <= nums.length <= 105
    -30 <= nums[i] <= 30
    The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf1(vector<int> &nums) {

        int sz = nums.size();
        if (sz <= 1)
            return nums;

        vector<int> prod(sz, 0);
        vector<int> left(sz, 0);
        vector<int> right(sz, 0);

        left[0] = 1;
        for (int i = 1; i < sz; i++) {
            left[i] = left[i - 1] * nums[i - 1];
        }

        right[sz - 1] = 1;
        for (int i = sz - 2; i >= 0; i--) {
            right[i] = right[i + 1] * nums[i + 1];
        }

        for (int i = 0; i < sz; i++) {
            prod[i] = left[i] * right[i];
        }

        return prod;
    }

    vector<int> productExceptSelf2(vector<int> &nums) {

        // Without extra space of left and right array
        int prod, n = nums.size();
        vector<int> ans(n);

        prod = 1;
        for (int i = 0; i < n; i++) {
            prod *= nums[i];
            ans[i] = prod;
        }

        prod = 1;
        for (int i = n - 1; i > 0; i--) {
            ans[i] = ans[i - 1] * prod;
            prod *= nums[i];
        }

        ans[0] = prod;

        return ans;
    }
};

void printArray(vector<int> vec, string msg) {
    cout << msg;
    for (auto v : vec) {
        cout << v << "  ";
    }
    cout << endl;
}

void test (vector<int> &vec) {
    Solution sol;
    printArray(vec, "Input array : ");
    auto res = sol.productExceptSelf2(vec);
    printArray(res, "Output product array : ");
}

int main(void) {
    vector<int> v = {1, 2, 3, 4};
    test(v);

    v = {-1, 1, 0, -3, 3};
    test(v);

    return 0;
}