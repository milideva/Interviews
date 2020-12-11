/*
On a 2-dimensional grid, there are 4 types of squares:

    1 represents the starting square.  There is exactly one starting square.
    2 represents the ending square.  There is exactly one ending square.
    0 represents empty squares we can walk over.
    -1 represents obstacles that we cannot walk over.

Return the number of 4-directional walks from the starting square to the ending
square, that walk over every non-obstacle square exactly once.

Example 1:

Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

Example 2:

Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

Example 3:

Input: [[0,1],[2,0]]
Output: 0
Explanation: 
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.

*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
            
    int isrc, jsrc;
    int m, n;
    int empty;
    vector<vector<bool>> visited;
    
  // Note that every emmpty cell must be covered - so count empty cells 
  // Since ALL empty cells need to be walked, we can not use shorted path => NO BFS, need DFS! 
  void findSrc (vector<vector<int>>& grid) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          isrc = i; jsrc = j;
        }
        if (grid[i][j] == 0)
          empty++;
      }
    }
  }
    
  int dfs (vector<vector<int>>& grid, int i, int j) {
    
    if (grid[i][j] == 2) {
      // reached destination
      if (!empty) 
        return 1; // covered all cells!
      return 0; // we reached shorter path - not covering all empty cells, return 0
    }
    int ret = 0;
    
    visited[i][j] = true;
    if (grid[i][j] == 0) 
      --empty;
    
    for (int k = 0; k < 4; k++) {
      static int rowAdj[] = { -1, 0, 0, +1 };
      static int colAdj[] = { 0, -1, +1, 0 };
      int iAdj = i + rowAdj[k];
      int jAdj = j + colAdj[k];
      if (iAdj < 0 || jAdj < 0 || iAdj >= m || jAdj >= n) 
        continue;
      if (visited[iAdj][jAdj])
        continue;
      if (grid[iAdj][jAdj] == -1) {
        visited[iAdj][jAdj] = true;
        continue;
      }
      ret += dfs(grid, iAdj, jAdj);
    }    
    // Back tracking 
    if (grid[i][j] == 0) 
      empty++;
    visited[i][j] = false; // back track
    return ret;
  }
  
public:
  int uniquePathsIII(vector<vector<int>>& grid) {
    
    m = grid.size();
    n = grid[0].size();
    findSrc(grid);
    visited.resize(m, vector <bool> (n, false));
    return dfs(grid, isrc, jsrc);
  }
};


int main () {
  class Solution sol;
  vector<vector<int>> grid = {{1,0,0,0},{0,0,0,0},{0,0,2,-1}};
  int count = sol.uniquePathsIII(grid);
  cout << "#unique paths: " << count << endl;
  return 0;
}
