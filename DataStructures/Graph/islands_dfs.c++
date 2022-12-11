/*

  200. Number of Islands

Given an m x n 2D binary grid grid which represents a map of '1's
(land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent
lands horizontally or vertically. You may assume all four edges of the
grid are all surrounded by water.

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 
Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.

*/

#include <vector>
#include <iostream>

using namespace std;

bool is_safe (vector<vector<char>>& grid, int i, int j) {
  int m = grid.size();
  int n = grid[0].size();
  if (i < 0 || j < 0) return false;
  if (i >= m || j >= n) return false;
  return true;
}
    

void count_islands_dfs (vector<vector<char>>& grid, int i, int j, 
                        vector<vector<bool>>& visited) {
  static int row_adj[] = {-1, 0, 0, +1};
  static int col_adj[] = {0, -1, +1, 0};
  
  visited[i][j] = true;
  
  for (int k = 0; k < 4; k++) {
    int row = i + row_adj[k];
    int col = j + col_adj[k];
    
    if (is_safe(grid, row, col) && (grid[row][col] == '1') && !visited[row][col]) {
      count_islands_dfs(grid, row, col, visited);
    }
  }
}

int numIslands (vector<vector<char>>& grid) {
        
  int m = grid.size();
  if (!m) return 0;
  int n = grid[0].size();
  vector <vector <bool>> visited;
  //vector<vector<bool>> visited(m, vector<bool> (n, false));
  visited.assign(m, vector <bool> (n, false));
  
  int count = 0;
  
  for (int i = 0; i < m; i++ ) {
    for (int j = 0; j < n; j++ ) {
      if (visited[i][j] == false &&  grid[i][j] == '1') {
        count_islands_dfs(grid, i, j, visited);
        count++;
      }
    }
  }
  
  return count;
}

int main () {

  vector<vector<char>> myvect = { { '1', '1', '1', '1', '0'}, 
                                 { '1', '1', '0', '1', '0'}, 
                                 { '1', '1', '0', '0', '0'},
                                 { '0', '0', '0', '1', '0'},
  };

  int count = numIslands(myvect);
  cout << "Num islands " << count << endl;
  return 0;
}
