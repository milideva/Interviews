/*
In a given grid, each cell can have one of three values:

    the value 0 representing an empty cell;
    the value 1 representing a fresh orange;
    the value 2 representing a rotten orange.

Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh
orange. If this is impossible, return -1 instead.

Example 1:

Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:

Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1

Explanation: The orange in the bottom left corner (row 2, column 0) is never
rotten, because rotting only happens 4-directionally.

Example 3:

Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.

*/

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
  vector <vector <int>> findRotten (vector<vector<int>>& grid, int r, int c, int &total) {
    vector <vector <int>> result;
    
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (grid[i][j]) total++;
        if (grid[i][j] == 2) {
          result.push_back({i, j});
        }
      }
    }
    return result;
  }
public:
    int orangesRotting (vector<vector<int>>& grid) {
      int r = grid.size();
      if (!r)  return 0;
      int c = grid[0].size();
      
      int i, j;
      i = j = 0;
      int total = 0;
      vector<vector <int>> rotV = findRotten(grid, r , c, total);
      
      if (rotV.size() == 0 && total) return -1;
      queue <pair<int, int>> q;
      for (auto v:rotV) {
        q.push({v[0], v[1]});
      }    
      
      int minutes = 0;
      
      while (!q.empty()) {
        int size = q.size();
        while (size--) {
          auto [i, j] = q.front(); q.pop();    
          
          int dx[] = { -1, 0, 0, +1};
          int dy[] = { 0, -1, +1, 0};
          for (int k = 0; k < 4; k++) {
            auto x = i + dx[k]; 
            auto y = j + dy[k];
            
            if (x < 0 || y < 0 || x >= r || y >= c)
                      continue;
            if (grid[x][y] == 1) {
              grid[x][y] = 2; // Infect the neighbor orange
              q.push({x, y});
            }
          }
          total--;
          grid[i][j] = 0; // clear this rotten orange or track visited.
        }
        if (!q.empty())
          minutes++;
      }
      if (total) return -1;
      return minutes;
    }
};


int main () {
  
  class Solution sol;

  vector <vector <int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
  int min = sol.orangesRotting(grid);

  cout << "Minutes :" << min  << endl;

  return 0;
}
