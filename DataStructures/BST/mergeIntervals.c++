/*

Given an array of intervals where intervals[i] = [starti, endi], merge all
overlapping intervals, and return an array of the non-overlapping intervals that
cover all the intervals in the input.

 

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
*/

#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Solution {
  map <int, int> calMap;
public:
  
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int len = intervals.size();
    if (len <=1) return intervals;
    
    for (auto v :intervals) {
      calMap[v[0]]++;
      calMap[v[1]]--;
    }
    
    vector<vector<int>> result;
    int count = 0;
    int start, end;
    for (auto e : calMap) {
      if (count == 0) {
        start = e.first;
      } 
      count += e.second;
      if (count == 0) {
        end = e.first;
        result.push_back({start, end});  
      }
    }
    
    return result;
  }
};

void print_vec(const std::vector<int>& vec) {
  cout << "[ ";
  for (auto x: vec) {
    cout << ' ' << x;
  }
  cout << " ]" << endl;
}

void print_vec_vec (vector<vector<int>>& vec) {
  cout << "[ " << endl;
  for (auto x: vec) {
    print_vec(x);
    cout << ' ' << endl;
  }
  cout << " ]" << endl;
}

int main () {
  class Solution sol;
  vector <vector <int>> intervals = {{1,3}, {2,6}, {8,10}, {15,18}};

  vector <vector <int>> res;

  res = sol.merge(intervals);
  print_vec_vec(res);

  intervals = {{7,10},{2,4}};
  res = sol.merge(intervals);
  print_vec_vec(res);

  return 0;
}

