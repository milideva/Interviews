
#include <iostream>
#include <vector>

using namespace std;

/*
    64. Minimum Path Sum

    Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

    Note: You can only move either down or right at any point in time.

    Example 1:
    Input: grid = [[1,3,1],[1,5,1],[4,2,1]]

    [1,3,1]
    [1,5,1]
    [4,2,1]

    Output: 7
    Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

    Example 2:
    Input: grid = [[1,2,3],[4,5,6]]
    Output: 12

    Constraints:
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 200
    0 <= grid[i][j] <= 100
*/
class Solution
{
    /* time limit exceeded */
    int minPathSumRecursive(vector<vector<int>> &grid, int i, int j)
    {
        if (i == 0 && j == 0)
        {
            return grid[i][j];
        }
        int csum = INT_MAX, rsum = INT_MAX;
        if (j > 0)
        {
            csum = minPathSumRecursive(grid, i, j - 1);
        }
        if (i > 0)
        {
            rsum = minPathSumRecursive(grid, i - 1, j);
        }
        return grid[i][j] + min(csum, rsum);
    }
    
    // With memoization - top down approach
    int minPathDP(vector<vector<int>> &grid, int i, int j,
                  vector<vector<int>> &dp)
    {
        if (i == 0 && j == 0)
        {
            return grid[i][j];
        }
        if (dp[i][j] != -1)
            return dp[i][j];

        int csum = INT_MAX, rsum = INT_MAX;

        if (i > 0)
        {
            rsum = minPathDP(grid, i - 1, j, dp);
        }

        if (j > 0)
        {
            csum = minPathDP(grid, i, j - 1, dp);
        }

        dp[i][j] = grid[i][j] + min(csum, rsum);
        return dp[i][j];
    }

    // With memoization - bottom up approach
    int minPathDP2(vector<vector<int>> &grid) 
    {
        int r = grid.size();
        int c = grid[0].size();

        vector<vector<int>> dp(r, vector<int>(c, 0));
        dp[0][0] = grid[0][0];

        // Initialize row 0
        for (auto j = 1; j < c; j++) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }
        // Initialize col 0
        for (auto i = 1; i < r; i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }
        for (auto i = 1; i < r; i++) {
            for (auto j = 1; j < c; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[r-1][c-1];
    }   

public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int r = grid.size();
        int c = grid[0].size();

        // vector<vector<int>> dp(r, vector<int>(c, -1));
        // return minPathSumRecursive(grid, r-1, c-1);
        // return minPathDP(grid, r - 1, c - 1, dp);
        return minPathDP2(grid);
    }
};

int main(void)
{

    vector<vector<int>> grid = {
        {5, 0, 1, 1, 2, 1, 0, 1, 3, 6, 3, 0, 7, 3, 3, 3, 1}, 
        {1, 4, 1, 8, 5, 5, 5, 6, 8, 7, 0, 4, 3, 9, 9, 6, 0}, 
        {2, 8, 3, 3, 1, 6, 1, 4, 9, 0, 9, 2, 3, 3, 3, 8, 4}, 
        {3, 5, 1, 9, 3, 0, 8, 3, 4, 3, 4, 6, 9, 6, 8, 9, 9}, 
        {3, 0, 7, 4, 6, 6, 4, 6, 8, 8, 9, 3, 8, 3, 9, 3, 4}, 
        {8, 8, 6, 8, 3, 3, 1, 7, 9, 3, 3, 9, 2, 4, 3, 5, 1}, 
        {7, 1, 0, 4, 7, 8, 4, 6, 4, 2, 1, 3, 7, 8, 3, 5, 4}, 
        {3, 0, 9, 6, 7, 8, 9, 2, 0, 4, 6, 3, 9, 7, 2, 0, 7}, 
        {8, 0, 8, 2, 6, 4, 4, 0, 9, 3, 8, 4, 0, 4, 7, 0, 4}, 
        {3, 7, 4, 5, 9, 4, 9, 7, 9, 8, 7, 4, 0, 4, 2, 0, 4}, 
        {5, 9, 0, 1, 9, 1, 5, 9, 5, 5, 3, 4, 6, 9, 8, 5, 6}, 
        {5, 7, 2, 4, 4, 4, 2, 1, 8, 4, 8, 0, 5, 4, 7, 4, 7}, 
        {9, 5, 8, 6, 4, 4, 3, 9, 8, 1, 1, 8, 7, 7, 3, 6, 9}, 
        {7, 2, 3, 1, 6, 3, 6, 6, 6, 3, 2, 3, 9, 9, 4, 4, 8}
        };

    Solution sol;
    int sum = sol.minPathSum(grid);
    cout << "sum: " << sum << endl;
    cout << "expected sum 83" << endl;
    return 0;
}
