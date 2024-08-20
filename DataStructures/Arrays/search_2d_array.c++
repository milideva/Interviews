/*
74. Search a 2D Matrix

ou are given an m x n integer matrix matrix with the following two properties:

Each row is sorted in non-decreasing order.
The first integer of each row is greater than the last integer of the previous row.
Given an integer target, return true if target is in matrix or false otherwise.

You must write a solution in O(log(m * n)) time complexity.

 

Example 1:


Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true
Example 2:


Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-104 <= matrix[i][j], target <= 104


*/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {

        int nr = matrix.size();
        int nc = matrix[0].size();
        
        int l = 0, r = nr * nc - 1;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            int midVal = matrix[mid / nc][mid % nc];

            if (midVal == target) 
                return true;
            if (midVal < target)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return false;
    }
};

void testSearchMatrix() {
    Solution sol;

    // Test Case 1: Basic Case (Target Present)
    {
        vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
        int target = 3;
        assert(sol.searchMatrix(matrix, target) == true);
    }

    // Test Case 2: Basic Case (Target Not Present)
    {
        vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
        int target = 13;
        assert(sol.searchMatrix(matrix, target) == false);
    }

    // Test Case 3: Single Element Matrix (Target Present)
    {
        vector<vector<int>> matrix = {{5}};
        int target = 5;
        assert(sol.searchMatrix(matrix, target) == true);
    }

    // Test Case 4: Single Element Matrix (Target Not Present)
    {
        vector<vector<int>> matrix = {{5}};
        int target = 1;
        assert(sol.searchMatrix(matrix, target) == false);
    }

    // Test Case 5: Target at Beginning of Matrix
    {
        vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
        int target = 1;
        assert(sol.searchMatrix(matrix, target) == true);
    }

    // Test Case 6: Target at End of Matrix
    {
        vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
        int target = 60;
        assert(sol.searchMatrix(matrix, target) == true);
    }

    // Test Case 7: Large Matrix with Negative Numbers
    {
        vector<vector<int>> matrix = {{-10, -5, 0, 5}, {10, 15, 20, 25}, {30, 35, 40, 45}};
        int target = -5;
        assert(sol.searchMatrix(matrix, target) == true);
    }

    // Test Case 8: Target Not Present in a Larger Matrix
    {
        vector<vector<int>> matrix = {{-10, -5, 0, 5}, {10, 15, 20, 25}, {30, 35, 40, 45}};
        int target = 50;
        assert(sol.searchMatrix(matrix, target) == false);
    }

    // Test Case 9: Edge Case (Empty Matrix)
    {
        vector<vector<int>> matrix = {};
        int target = 1;
        // assert(sol.searchMatrix(matrix, target) == false); // Uncomment if you handle empty matrices.
    }

    // Test Case 10: Edge Case (Target Less than All Elements)
    {
        vector<vector<int>> matrix = {{2, 3, 5}, {7, 8, 10}, {12, 15, 20}};
        int target = 1;
        assert(sol.searchMatrix(matrix, target) == false);
    }

    // Test Case 11: Edge Case (Target Greater than All Elements)
    {
        vector<vector<int>> matrix = {{2, 3, 5}, {7, 8, 10}, {12, 15, 20}};
        int target = 21;
        assert(sol.searchMatrix(matrix, target) == false);
    }

    cout << "All test cases passed!" << endl;
}

int main() {
    testSearchMatrix();
    return 0;
}