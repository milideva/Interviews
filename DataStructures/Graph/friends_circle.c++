/*

There are N students in a class. Some of them are friends, while some are not.
Their friendship is transitive in nature. For example, if A is a direct friend
of B, and B is a direct friend of C, then A is an indirect friend of C. And we
defined a friend circle is a group of students who are direct or indirect
friends.

Given a N*N matrix M representing the friend relationship between students in
the class. If M[i][j] = 1, then the ith and jth students are direct friends with
each other, otherwise not. And you have to output the total number of friend
circles among all the students.

Example 1:

Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2

Explanation:The 0th and 1st students are direct friends, so they are in a friend
circle. The 2nd student himself is in a friend circle. So return 2.

Example 2:

Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1

Explanation:The 0th and 1st students are direct friends, the 1st and 2nd
students are direct friends, so the 0th and 2nd students are indirect friends.
All of them are in the same friend circle, so return 1.

*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {

  vector <bool> visited;
  
  void dfs (vector<vector<int>>& M, int i) {
    // Mark node as visited
    visited[i] = true;
    
    // For all edges (other friends) 
    for (int j = 0; j < M[i].size(); j++) {
      // If node is a friend and if not visited yet
      if (M[i][j] && visited[j] == false) {
        dfs(M, j);
      }
    }
  }
    
public:
  int findCircleNum (vector <vector<int>>& M) {
    int n = M.size();
    if (!n) return 0;
    
    // Mark all visited as false
    visited.resize(n, false); // dynamic size + init to false

    int count = 0;

    // For each node (each student)
    for (int i = 0; i < n; i++) {
      if (visited[i] == false) {
        // If not visited, pay a visit
        dfs(M, i);
        count++;
      }            
    }
    return count;
  }
};

int main() {

  vector <vector <int>> mat =
    {
      { 1, 0, 0, 1, 0, 0, 0 },
      { 0, 1, 1, 0, 0, 0, 0 },
      { 0, 1, 1, 0, 0, 0, 1 },
      { 1, 0, 0, 1, 1, 0, 1 },
      { 0, 0, 0, 1, 1, 0, 0 },
      { 0, 0, 0, 0, 0, 1, 0 },
      { 0, 0, 1, 1, 0, 0, 1 }
    };

  class Solution sol;
  unsigned dist = sol.findCircleNum(mat);
  
  cout << "#Friend circles : " << dist << endl;
  
  return 0;
}
