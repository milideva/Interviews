/*

Leetcode 695. Max Area of Island

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's
(representing land) connected 4-directionally (horizontal or vertical.) You may
assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no
island, the maximum area is 0.)

Example 1:

[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]

Given the above grid, return 6. Note the answer is not 11, because the island
must be connected 4-directionally.

Example 2:

[[0,0,0,0,0,0,0,0]]

Given the above grid, return 0.

Note: The length of each dimension in the given grid does not exceed 50.

Time : O(m*n)
Space : O(1)
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
  vector <vector <bool>> visited;
  int r, c;
  
  bool isSafe (int x, int y) {
    return x < r && x >= 0  && y >= 0 && y < c;
  }
  
  int dfs_2 (vector<vector<int>>& grid, int i, int j) {
    visited[i][j] = true;
    int count = 1;
    
    int rAdj[] = { -1, 0, 0, +1};
    int cAdj[] = { 0, -1, +1, 0};
    
    for (int k = 0; k < 4; k++) {
      int dx = i + rAdj[k];
      int dy = j + cAdj[k];
      if (isSafe(dx, dy) == false)
        continue;
      if (grid[dx][dy] && visited[dx][dy] == false) {
        count += dfs(grid, dx, dy);
      }
    }
    return count; 
  }
  
  int dfs(vector<vector<int>>& grid, int i, int j) {
    // Check all error conditions 
    // 1. Check if off the size
    if (i < 0 || i == grid.size() || j < 0 || j == grid[0].size())
      return 0;
    // 2. Check if grid is not set
    if (grid[i][j] != 1)
      return 0;
    // 3. Check if already visited
    if (visited[i][j])
      return 0;

    // Mark visited first
    visited[i][j] = true;

    // try all 4 paths
    return 1 +
           dfs(grid, i + 1, j) + dfs(grid, i - 1, j) +
           dfs(grid, i, j + 1) + dfs(grid, i, j - 1);
  }

public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    r = grid.size();
    c = grid[0].size();
    
    visited.resize(r, vector<bool>(c, false));
    
    if (!r) return 0;
    int maxArea = 0;
    
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (grid[i][j] && visited[i][j] == false)
          maxArea = max(maxArea, dfs_2(grid, i, j));
      }
    }
    return maxArea;
  }
};
  
int main () {
  
  vector<vector<int>> grid = {{0,0,1,0,0,0,0,1,0,0,0,0,0},
                              {0,0,0,0,0,0,0,1,1,1,0,0,0},
                              {0,1,1,0,1,0,0,0,0,0,0,0,0},
                              {0,1,0,0,1,1,0,0,1,0,1,0,0},
                              {0,1,0,0,1,1,0,0,1,1,1,0,0},
                              {0,0,0,0,0,0,0,0,0,0,1,0,0},
                              {0,0,0,0,0,0,0,1,1,1,0,0,0},
                              {0,0,0,0,0,0,0,1,1,0,0,0,0}};
  
  class Solution sol;
  int max = sol.maxAreaOfIsland(grid);
  cout << "Max area of island:" << max << endl;
  
  return 0;
}
