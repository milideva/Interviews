/*

Given a set of non-overlapping intervals, insert a new interval into the
intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times. 

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

Example 3:

Input: intervals = [], newInterval = [5,7]
Output: [[5,7]]

Example 4:

Input: intervals = [[1,5]], newInterval = [2,3]
Output: [[1,5]]

Example 5:

Input: intervals = [[1,5]], newInterval = [2,7]
Output: [[1,7]]

*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {

public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> res;
    size_t i = 0;
    
    // Left part (no intersection with newInterval)
    while (i < intervals.size() && intervals[i][1] < newInterval[0]) {
      res.push_back(intervals[i]);
      ++i;
    }
    
    // newInterval part (with or without merge)
    while (i < intervals.size() && intervals[i][0] <= newInterval[1]) {
      newInterval[0] = min(newInterval[0], intervals[i][0]);
      newInterval[1] = max(newInterval[1], intervals[i][1]);
      ++i;
    }
    res.push_back(newInterval);
    
    // Right part (no intersection with newInterval)
    while (i < intervals.size() && intervals[i][0] > newInterval[1]) {
      res.push_back(intervals[i]);
      ++i;
    }
    return res;
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
  vector <int> newIntervals = { 9, 16 };
  vector <vector <int>> res;

  res = sol.insert(intervals, newIntervals);
  print_vec_vec(res);

  return 0;
}

