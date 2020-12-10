/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.

 

Example 1:

Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:

Input: obstacleGrid = [[0,1],[0,0]]
Output: 1

*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        int dp[m][n];
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                if (i == 0 || j == 0) {
                    if (obstacleGrid[i][j] != 1) {
                        if (!i && !j) dp[i][j] = 1;
                        if (!i && j) dp[i][j] = dp[i][j-1];
                        if (!j && i) dp[i][j] = dp[i-1][j];
                    } else {
                        dp[i][j] = 0;
                    }
                    continue;
                }
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                    continue;
                }
                dp[i][j]  = dp[i][j-1] + dp[i-1][j];
                
            }
        }
        
        return dp[m-1][n-1];
    }
};


int main () {
  class Solution sol;
  int count;
  vector <vector <int>> grid = { {0,0,0}, {0,1,0}, {0,0,0} };
  count = sol.uniquePathsWithObstacles(grid);
  cout << "#Unique paths: " << count << endl;

  return 0;
}
