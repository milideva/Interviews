/*
283. Move Zeroes

Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

Example 1:

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
Example 2:

Input: nums = [0]
Output: [0]
 

Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {

public:
    void moveZeroes (vector<int>& nums) {
        int sz = nums.size();
        int writePtr = 0;
        for (auto num: nums) {
            if (num != 0) {
                nums[writePtr++] = num;
            }
        }
        while (writePtr < sz) {
            nums[writePtr++] = 0;
        }
        return; 
    }
    void printVector (vector<int>& vect) {
        for (int x : vect)
            cout << x << " ";
        cout << endl;
    }
};

void test (vector<int> &v) {
    class Solution sol;
    sol.moveZeroes(v);
    sol.printVector(v);
}

int main () {
    vector <int> v{0,1,0,3,12};
    test(v);

    return 0;
}