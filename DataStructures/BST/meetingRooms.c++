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

/*
 
 https://leetcode.com/problems/meeting-rooms-ii/discuss/203658/HashMapTreeMap-resolves-Scheduling-Problem

 Here is the idea -

 Load all intervals to the TreeMap, where keys are intervals'
 start/end boundaries, and values accumulate the changes at that point
 in time.

 Traverse the TreeMap (in other words, sweep the timeline). If a new
 interval starts, increase the counter (k value) by 1, and the counter
 decreases by 1, if an interval has finished.

 Calcalulate the number of the active ongoing intervals.

*/

#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Solution {
  map <int, int> calMap;
  bool canAdd (int maxConflicts) {
    int count = 0;
    for (auto [t, cnt] : calMap) {
      count += cnt;
      if (count > maxConflicts) 
        return false;
    }
    return true; 
  }
public:
  bool canAttendMeetings(vector<vector<int>>& intervals) {
    if (intervals.size() <= 1) return true;
    
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
