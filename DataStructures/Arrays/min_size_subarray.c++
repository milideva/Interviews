/*

Test Result
209. Minimum Size Subarray Sum

Given an array of positive integers nums and a positive integer target, return the minimal length of a 
subarray
whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

 

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1
Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
 

Constraints:

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 104
 

Follow up: If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log(n)).

*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector <int>& nums) {
        auto sz = nums.size();
        int l = 0, r = 0;
        int minLen = sz + 1;
        long sum = 0;
        
        while (l < sz && r < sz) {
            sum += nums[r];

            while (sum >= target) {
                auto len = r - l + 1;
                minLen = min(minLen, len);
                sum = sum - nums[l];
                l++;
            }
            r++;
        }
        return (minLen == sz + 1) ? 0 : minLen;
    }
};

// print vector
void printVector (vector <int>& v) {
    for (auto& i : v) {
        cout << i << " ";
    }
    cout << endl;
}

void test (int target, vector <int>& nums) {
    Solution sol;
    
    auto len = sol.minSubArrayLen(target, nums);
    printVector(nums);
    cout << "target: " << target << " min subarray len: " << len << endl;
}

int main (void) {
    class Solution sol;
    vector <int> v {2,3,1,2,4,3};
    test(7, v);
    test(4, v);
    test(11, v);

    vector <int> v1 {1,4,4};
    test(4, v1);

    return 0;
}