/*
Given an array of meeting time intervals where intervals[i] = [starti, endi],
determine if a person could attend all meetings.

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: false

Example 2:

Input: intervals = [[7,10],[2,4]]
Output: true

Constraints:
    0 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti < endi <= 106
*/

#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Solution {
  map <int, int> calMap;
  bool canAdd (int maxConflicts) {
    int count = 0;
    for (auto e : calMap) {
      count += e.second;
      if (count > maxConflicts) 
        return false;
    }
    return true; 
  }
public:
  bool canAttendMeetings(vector<vector<int>>& intervals) {
    int len = intervals.size();
    if (len == 0) return true;
    
    if (len == 1) return true;
    
    for (auto v :intervals) {
      calMap[v[0]]++;
      calMap[v[1]]--;
    }
    
    int maxConflicts = 1;
    return canAdd(maxConflicts);
  }
};

int main () {
  class Solution sol;
  vector <vector <int>> intervals = {{0,30},{5,10},{15,20}};
  bool can = sol.canAttendMeetings(intervals);
  cout << "Can attend 1: " << can << endl;
  
  class Solution sol2;
  intervals = {{7,10},{2,4}};
  
  can = sol2.canAttendMeetings(intervals);
  cout << "Can attend 2: " << can << endl;
  
  return 0;
}
