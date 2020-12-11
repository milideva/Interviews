/*

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

You may return the answer in any order.

Example 1:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

Example 2:

Input: n = 1, k = 1
Output: [[1]]

 
Constraints:

    1 <= n <= 20
    1 <= k <= n

*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {

public:
  void combine (vector< vector<int> >& result, vector <int>& curr, int start, int n, int k) {
    if (k == 0) {
      result.push_back(curr);
      return;
    }
    for (int i =  start; i <= n; i++) {
      curr.push_back(i);          
      combine(result, curr, i+1, n, k-1);
      curr.pop_back();
    }
    return;
  }

  vector< vector<int> > combine (int n, int k) {
    vector < vector <int> > result;
    vector <int> curr;
    int start = 1;
    combine(result, curr, start, n, k);
    return result;        
  }
};

void print ( vector < vector <int> > &res) {
  for (auto v : res) {
    cout << "\n[ ";
    for (auto i : v) {
      cout << " " << i;
    }
    cout << " ]" << endl;
  } 
}

int main () {
  Solution sol;
  vector < vector <int> > res = sol.combine(5, 3);
  
  print(res);	
  return 0;
}
