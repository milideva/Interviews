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
using namespace std;

class Solution {
    static bool cmpInt (vector<int> &v1, vector<int>& v2 ) {
        return v1[0] < v2[0];
    }
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int len = intervals.size();
        if (len == 0) return 0;
        
        vector <int> start, end;
        for (auto v: intervals) {
            start.push_back(v[0]); 
            end.push_back(v[1]); 
        }
        sort(start.begin(), start.end());
        sort(end.begin(), end.end());
        
        int s, e;
        s = e = 0;
        int nrooms = 0;
        int max = 0;
        while (s < len && e < len) {
            if (start[s] < end[e]) {
                nrooms++;
                max = nrooms > max ? nrooms : max;
                s++;
                continue;
            }
            e++;
            nrooms--;   
        }
        
        return max;
    }
};

int main () {
  class Solution sol;
  vector <vector <int>> intervals = {{0,30},{5,10},{15,20}};
  int min = sol.minMeetingRooms(intervals);
  cout << "Min meeting roooms 1: " << min << endl;

  intervals = {{7,10},{2,4}};

  min = sol.minMeetingRooms(intervals);
  cout << "Min meeting rooms 2: " << min << endl;

  return 0;
}
