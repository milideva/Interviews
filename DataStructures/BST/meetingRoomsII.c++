/*
Given an array of meeting time intervals consisting of start and end times
[[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms
required.

Example 1:

Input: [[0, 30],[5, 10],[15, 20]]
Output: 2

Example 2:

Input: [[7,10],[2,4]]
Output: 1
*/

#include <vector>
#include <iostream>
#include <map>

using namespace std;

class Solution {
  map <int, int> calMap;
  
  int canAdd () {
    int count = 0;
    int maxK = 0;
    
    for (auto e : calMap) {
      count += e.second;
      maxK = max(maxK, count);
    }
    return maxK;
  }
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int len = intervals.size();
        if (len == 0) return 0;
        if (len == 1) return true;

        for (auto v :intervals) {
          calMap[v[0]]++;
          calMap[v[1]]--;
        }
        return canAdd();
    }
};

int main () {
  class Solution sol;
  vector <vector <int>> intervals = {{0,30},{5,10},{15,20}};
  int min = sol.minMeetingRooms(intervals);
  cout << "Min meeting roooms 1: " << min << endl;

  class Solution sol2;
  intervals = {{7,10},{2,4}};

  min = sol2.minMeetingRooms(intervals);
  cout << "Min meeting rooms 2: " << min << endl;

  return 0;
}
