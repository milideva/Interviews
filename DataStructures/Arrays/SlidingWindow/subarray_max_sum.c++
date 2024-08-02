#include <vector>
#include <iostream>

using namespace std;

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
            continue;
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
}