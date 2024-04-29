#include <vector>
#include <iostream>

using namespace std;


/*
    179. Largest Number

    Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.
    Since the result may be very large, so you need to return a string instead of an integer.
    
    Example 1:
    Input: nums = [10,2]
    Output: "210"
    
    Example 2:
    Input: nums = [3,30,34,5,9]
    Output: "9534330"
     
    Constraints:
    1 <= nums.length <= 100
    0 <= nums[i] <= 109
*/

void print (vector <int> &nums, string prefix) {
    cout << prefix ;
    for (auto n: nums) {
        cout << " " << n ;
    }
    cout << endl;
}

/*

Before sorting :  10 2
After sorting :  2 10
answer: 210

Before sorting :  3 30 34 5 9
After sorting :  9 5 34 3 30
answer: 9534330

*/
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        print(nums, "Before sorting : ");
        sort(nums.begin(), nums.end(), [](int a, int b){
          return to_string(a)+to_string(b) > to_string(b)+to_string(a);
        });
        print(nums, "After sorting : ");
        
        string ans;
        for (int i = 0; i < nums.size(); i++) {
            ans += to_string(nums[i]);
        }
        
        if (ans[0] == '0')
            return "0";
        
        return ans; 
    }
};

void test (vector <int> nums) {
    Solution sol;
    auto str = sol.largestNumber(nums);
    cout << "answer: " << str << endl << endl;
}

int main (void) {
    test({10,2});
    test({3,30,34,5,9});
    return 0;
}