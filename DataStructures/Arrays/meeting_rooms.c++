
/*

Given an array of meeting time intervals where intervals[i] = [starti, endi],
determine if a person could attend all meetings.

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: false

Example 2:

Input: intervals = [[7,10],[2,4]]
Output: true
*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {

public:
  bool canAttendMeetings(vector<vector<int>>& intervals) {
    int len = intervals.size();
    if (len == 0) return true;
    
    if (len == 1) return true;
    
    vector<int> start, end;
    
    for (auto v : intervals) {
      start.push_back(v[0]);
      end.push_back(v[1]);
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());
    
    int rooms; 
    int i, j;
    i = j = rooms = 0;
    
    while (i < len && j < len) {
      if (start[i] < end[j]) {
        rooms++;
        if (rooms > 1) 
          return false;
        i++;
        continue;
      }
      j++;
      rooms--;
    }
    return true;
  }
};

int main () {
  class Solution sol;
  vector <vector <int>> intervals = {{0,30},{5,10},{15,20}};
  bool can = sol.canAttendMeetings(intervals);
  cout << "Can attend 1: " << can << endl;

  intervals = {{7,10},{2,4}};

  can = sol.canAttendMeetings(intervals);
  cout << "Can attend 2: " << can << endl;

  return 0;
}
