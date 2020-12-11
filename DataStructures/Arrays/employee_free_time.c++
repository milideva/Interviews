
/*

We are given a list schedule of employees, which represents the working time for
each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are
in sorted order.

Return the list of finite intervals representing common, positive-length free
time for all employees, also in sorted order.

(Even though we are representing Intervals in the form [x, y], the objects
inside are Intervals, not lists or arrays. For example, schedule[0][0].start =
1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined). Also, we
wouldn't include intervals like [5, 5] in our answer, as they have zero length. 

Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation: There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.

Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]
 
*/


#include <vector>
#include <iostream>
using namespace std;

class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};

class Solution {
  static bool cmp (Interval &a, Interval &b) {
    return a.start < b.start;
  }
public:
  vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
    vector <Interval> all;
    vector <Interval> result;
    
    for (auto vInt : schedule) {
      for (auto anInterval : vInt) {
        all.push_back(anInterval);
      }
    }
        
    sort(all.begin(), all.end(), cmp); // by default sort() sorts on first element of a pair
    
    auto prev = all[0];
    auto lastEnd = prev.end;
    
    for (int i = 1; i < all.size(); i++) {
      auto curr = all[i];
      if (curr.start < lastEnd) { // we've an overlap
        // see if we need to update lastEnd
        lastEnd = max(lastEnd, curr.end);
      } else {
        // we've a gap between lastend to curr.start
        if (lastEnd != curr.start) {
          result.push_back({lastEnd, curr.start});
        }
        lastEnd = curr.end;
      }
      
    }
    return result;
  }
};


void print_vec(const std::vector<Interval>& vec) {
  cout << "[ " ;
  for (auto [x, y]: vec) {
    cout << " ("<< x << ", " << y << ") , ";
  }
  cout << " ]" << endl;
}

int main () {
  class Solution sol;
  vector <vector <Interval>> intervals = {{ {1,3}, {6,7} },  { {2,4} }, { {2,5}, {9,12}} };
  vector <Interval> res;

  res = sol.employeeFreeTime(intervals);
  print_vec(res);

  return 0;
}

