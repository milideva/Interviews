
/*

Given a 2D grid consists of 0s (land) and 1s (water). An island is a maximal
4-directionally connected group of 0s and a closed island is an island totally
(all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

 

Example 1:

Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
Output: 2
Explanation: 
Islands in gray are closed because they are completely surrounded by water (group of 1s).

Example 2:

Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1

Example 3:

Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2

 

Constraints:

    1 <= grid.length, grid[0].length <= 100
    0 <= grid[i][j] <=1

*/

#include <vector>

#include <iostream>

using namespace std;

class Solution {
    int rows, cols;
    vector <vector <bool>> visited;
    
    int x[4] = {-1,0,1,0};
    int y[4] = {0,1,0,-1};
    
    void dfs (int i, int j, vector<vector<int>>& grid, bool &flag) { 
        // First mark the node visited.     
        visited[i][j] = true;

        // A closed island, needs to be completely surrounded by water.
        if (i == 0 or j == 0 or i == rows-1 or j == cols-1) {
            flag = true; // // not a closed island
            return;
        }
        for (int k = 0; k < 4; k++) {
            int xn = x[k] + i;
            int yn = y[k] + j;
            if (xn >= 0 and xn < rows and yn >= 0 and yn < cols) {
                if (grid[xn][yn] == 0 && visited[xn][yn] == false) {
                    dfs(xn, yn, grid, flag);
                }
            }
        }
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        rows = grid.size();
        if (!rows) return 0;
        cols = grid[0].size();
        int count = 0;
        
        visited.resize(rows, vector<bool> (cols, false));
        
        // Skip edges for closed islands by starting with 1 instead of 0
        // and ending with < rows-1 instead of < rows
        for (int i = 1; i < rows-1; i++) {
            for (int j = 1; j < cols-1; j++) {
                if (grid[i][j] == 0 && visited[i][j] == false) {
                    bool flag = false;
                    dfs(i, j, grid, flag);
                    if (flag == true) {
                        // skip counting it
                    } else {
                        count++;
                    }
                }
            }
        }
        return count;
    }
};


int main (void) {

  vector<vector<int>> myvect = { { 1, 1, 1, 1, 0}, 
                                 { 1, 0, 1, 0, 1}, 
                                 { 1, 1, 0, 1, 0},
                                 { 0, 1, 0, 0, 0},
  };

  Solution sol;
  int count = sol.closedIsland(myvect);
  cout << "Num closeed islands " << count << endl;

  return 0;
}
