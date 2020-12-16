/*

Given an m x n matrix, return all elements of the matrix in spiral order.

Example 1:

1 2 3
4 5 6
7 8 9

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:

1 2  3  4
5 6  7  8
9 10 11 12

Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int r = matrix.size();
    int c = matrix[0].size();
    
    vector <int> res;
    if (!r) return res;
    
    int r1, c1;
    int r2, c2;
    r1 = c1 = 0;
    r2 = r-1;
    c2 = c-1;
    
    while (r1 <= r2 && c1 <= c2) {
      // top layer row
      for (int j = c1; j <= c2; j++) 
        res.push_back(matrix[r1][j]);
      // right layer col
      for (int i = r1+1; i <= r2; i++) 
        res.push_back(matrix[i][c2]);
      if (r1 < r2 && c1 < c2) {
        // bottom layer row
        for (int j = c2-1; j > c1; j--) 
          res.push_back(matrix[r2][j]);
        // left layer col
        for (int i = r2; i > r1; i--) 
          res.push_back(matrix[i][c1]);
      }
      r1++; r2--; c1++; c2--;
    }
    
    return res;        
  }
};

int main () {

  vector <vector <int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

  class Solution sol;
  vector <int> result = sol.spiralOrder(matrix);
  for (auto i: result) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
