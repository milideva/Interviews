/*

994. Rotting Oranges

You are given an m x n grid where each cell can have one of three values:

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

/*
  Time : O(m * n)
  Space : O(m * n)
*/

class Solution {
public:
  int orangesRotting(vector<vector<int>>& grid) {
    const int m = grid.size();
    const int n = grid[0].size();
    int ans = 0;
    int countFresh = 0;
    queue<pair<int, int>> q;

    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (grid[i][j] == 1)
          ++countFresh;
        else if (grid[i][j] == 2)
          q.emplace(i, j);

    if (countFresh == 0)
      return 0;

    constexpr int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!q.empty()) {
      ++ans;
      for (int sz = q.size(); sz > 0; --sz) {
        const auto [i, j] = q.front();
        q.pop();
        for (const auto& [dx, dy] : dirs) {
          const int x = i + dx;
          const int y = j + dy;
          if (x < 0 || x == m || y < 0 || y == n)
            continue;
          if (grid[x][y] != 1)
            continue;
          grid[x][y] = 2;   // Mark grid[x][y] as rotten.
          q.emplace(x, y);  // Push the newly rotten orange to the queue.
          --countFresh;     // Decrease the count of fresh oranges by 1.
        }
      }
    }

    return countFresh == 0 ? ans - 1 : -1;
  }
};


int main () {
  
  class Solution sol;

  vector <vector <int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
  int min = sol.orangesRotting(grid);

  cout << "Minutes :" << min  << endl;

  return 0;
}
