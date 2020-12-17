/*

On a 2 dimensional grid with R rows and C columns, we start at (r0, c0) facing east.

Here, the north-west corner of the grid is at the first row and column, and the
south-east corner of the grid is at the last row and column.

Now, we walk in a clockwise spiral shape to visit every position in this grid. 

Whenever we would move outside the boundary of the grid, we continue our walk
outside the grid (but may return to the grid boundary later.)

Eventually, we reach all R * C spaces of the grid.

Return a list of coordinates representing the positions of the grid in the order
they were visited. 

Example 1:

Input: R = 1, C = 4, r0 = 0, c0 = 0
Output: [[0,0],[0,1],[0,2],[0,3]]

Example 2:

Input: R = 5, C = 6, r0 = 1, c0 = 4

Output:
[[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]

*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {

  /*
    Walk in a Spiral
    Intuition
    
    We can walk in a spiral shape from the starting square, ignoring whether we stay
    in the grid or not. Eventually, we must have reached every square in the grid.
    
    Algorithm
    
    Examining the lengths of our walk in each direction, we find the following
    pattern: 1, 1, 2, 2, 3, 3, 4, 4, ... That is, we walk 1 unit east, then 1 unit
    south, then 2 units west, then 2 units north, then 3 units east, etc. Because
    our walk is self-similar, this pattern repeats in the way we expect.
    
  */

public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        
        // 1 1 2 2 3 3 4 4 5 5 6 6
        // 0 1 2 3 4 5 6 8 7 8 9 10* increase if it is in the odd number
        int rpos = r0, cpos = c0, dir = 0, go = 1;
        int cnt = 0, ans_cnt = 0;
        int dr[4] = {0, 1, 0, -1};
        int dc[4] = {1, 0, -1, 0};
        vector<vector<int>> res;

        //push back the start position
        res.push_back({rpos, cpos});
        ans_cnt++;
        while (ans_cnt < R * C) {
            for (int i = 1; i <= go; i++) {
                rpos += dr[dir];
                cpos += dc[dir];
                if(rpos >= 0 && rpos < R && cpos >=0 && cpos < C) {
                    res.push_back({rpos, cpos});
                    ans_cnt++;
                }
            }
            //to make  1 1 2 2 3 3 4 4 5 5 sequence
            if (cnt & 1)  {
                go++;
            }
        
            cnt++;
            dir++;
            dir %= 4; //change direction
        }
        return res;
    }
};

int main () {

  int R, C, r0, c0;
  R = 5, C = 6, r0 = 1, c0 = 4;
  
  class Solution sol;
  vector<vector<int>> res = sol.spiralMatrixIII(R, C, r0, c0);
  
  for (auto v : res)  {
      cout << "[" << v[0] << "," << v[1] << "] " ;
    }
  cout << endl;
  return 0;
}
