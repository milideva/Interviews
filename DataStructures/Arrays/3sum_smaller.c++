#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    Given an array of n integers nums and an integer target, find the
    number of index triplets i, j, k with 0 <= i < j < k < n that satisfy
    the condition nums[i] + nums[j] + nums[k] < target.

    Example 1:
    Input: nums = [-2,0,1,3], target = 2
    Output: 2
    Explanation: Because there are two triplets which sums are less than 2:
    [-2,0,1]
    [-2,0,3]

    Example 2:
    Input: nums = [], target = 0
    Output: 0

    Example 3:
    Input: nums = [0], target = 0
    Output: 0
*/

class Solution
{
    int twoSumSmaller(vector<int> &nums, int startI, int target)
    {
        int l = startI;
        int r = size(nums) - 1;
        int ret = 0;
        while (l < r)
        {
            if (nums[l] + nums[r] < target)
            {
                ret += r - l; // this is the trick to optimize, add all pairs less than r.
                l++;
                continue;
            }
            r--;
        }
        return ret;
    }

public:
    int threeSumSmaller(vector<int> &nums, int target)
    {
        int ans = 0;
        /*
        // If you need original index:
        unordered_map <int, int> num2i;

        for (auto i = 0; i < size(nums); i++) {
            nums2i[nums[i]] = i; // save original index ordering
        }
        */
        if (size(nums) < 3)
            return ans;
        sort(begin(nums), end(nums)); // nLog(n)

        // O(n^2)
        for (auto i = 0; i < size(nums) - 2; i++)
        {
            ans += twoSumSmaller(nums, i + 1, target - nums[i]);
        }
        return ans;
    }
};

int main()
{
    vector<int> nums = {-4, -3, 0, 3, 10, 20};
    vector<int> nums2 = {-2, 0, 1, 3};
    class Solution sol;
    auto target = 0;
    auto ans = sol.threeSumSmaller(nums, target);

    cout << "For nums: answer:" << ans << " target:" << target << endl;

    target = 2;
    ans = sol.threeSumSmaller(nums2, target);
    cout << "For nums2 : answer:" << ans << " target:" << target << endl;
    return 0;
}
