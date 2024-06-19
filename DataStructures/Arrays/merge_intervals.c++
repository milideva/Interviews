
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
using namespace std;

class Solution {
  static bool cmp (vector<int>& a, vector<int> &b) {
    return a[0] < b[0];
  }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> ans;

    ranges::sort(intervals);

    for (const vector<int>& interval : intervals)
      if (ans.empty() || ans.back()[1] < interval[0])
        ans.push_back(interval);
      else
        ans.back()[1] = max(ans.back()[1], interval[1]);

    return ans;
  }
  
  // vector<vector<int>> merge (vector<vector<int>>& intervals) {
  //   int len = intervals.size();
  //   if (len <=1) return intervals;
    
  //   sort(intervals.begin(), intervals.end(), cmp);
  //   vector<vector<int>> result;
    
  //   result.push_back(intervals[0]);
  //   for (int i = 1; i < len; i++) {
  //     if (intervals[i][0] > result.back()[1]) {
  //       result.push_back(intervals[i]);
  //       continue;
  //     }
  //     result.back()[1] = max(result.back()[1],  intervals[i][1]);
  //   }
    
  //   return result;
  // }
  
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
