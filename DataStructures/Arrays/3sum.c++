#include <iostream>
#include <vector>

using namespace std;


<vector<vector <int>> 3sum (vector <int> &nums) {

    <vector<vector <int>> result;
    // This is with sorting allowed. If sorting not allowed, this method wont work
    sort(nums.begin(), nums.end());

    for (int i=0; i < nums.size() - 2; i++) {
        if (i > 0 && nums[i] == nums[i-1]) 
            continue;

            int l = i+1;
            int r = nums.end()-1;

            while (l <= r) {
                int s = nums[i] + nums[l] + nums[r];
                if (s == 0) {
                    result.push_back(vector <int> { nums[i], nums[l], nums[r] };                   
                   while (l+1 <  nums.size()) l++; r--; 
                    continue;
                } 
                if (s < 0) l++; 
                if (s > 0) r--;
            }
    }

}
