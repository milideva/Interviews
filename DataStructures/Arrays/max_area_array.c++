/*

11. Container With Most Water

You are given an integer array height of length n. 
There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. 
In this case, the max area of water (blue section) the container can contain is 49.


Input: height = [1,1]
Output: 1

Constraints:
n == height.length
2 <= n <= 105
0 <= height[i] <= 104

*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
    int min (int a, int b) {
        return a < b ? a : b;
    }

    int getArea (vector <int>& height, int i, int j) {
        if (i < 0 || i >= height.size())
            return 0;
        if (j < 0 || j >= height.size())
            return 0;
        return min(height[i], height[j]) * abs(j - i);
    }

public:
    int maxArea (vector <int>& height) {
        int sz = height.size();
        int maxArea = 0;
        int l = 0;
        int r = sz - 1;
        while (l < r) {
            int area = getArea(height, l, r);
            if (area > maxArea) {
                maxArea = area;
            }
            if (height[l] > height[r]) {
                r--;
            } else {
                l++;
            }
        }
        return maxArea;
    }
};

int main (void) {
    class Solution sol;
    vector <int> v {1,8,6,2,5,4,8,3,7};
    auto area = sol.maxArea(v);
    cout << "max area: " << area << endl;
    return 0;
}