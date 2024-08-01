/*

Implement a MyCalendar class to store your events. A new event can be added if
adding the event will not cause a double booking.

Your class will have the method, book(int start, int end). Formally, this
represents a booking on the half open interval [start, end), the range of real
numbers x such that start <= x < end.

A double booking happens when two events have some non-empty intersection (ie.,
there is some time that is common to both events.)

For each call to the method MyCalendar.book, return true if the event can be
added to the calendar successfully without causing a double booking. Otherwise,
return false and do not add the event to the calendar. Your class will be called
like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)

Example 1:

MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(15, 25); // returns false
MyCalendar.book(20, 30); // returns true
Explanation: 
The first event can be booked.  The second can't because time 15 is already booked by another event.
The third event can be booked, as the first event takes every time less than 20, but not including 20.

 

Note:

    The number of calls to MyCalendar.book per test case will be at most 1000.
    In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].

*/

#include <set>
#include <map>
#include <iostream>

using namespace std;

class MyCalendar {
  set <pair <int, int>> cal; // set is an ordered data structure

public:
    MyCalendar() {   
    }
    
  bool book(int start, int end) {
    auto curr = cal.lower_bound({start, end}); // lower_bound returns first >= element

    // check curr's start < end
    if (curr != cal.end() && curr->first < end) {

      return false;
    }
    if (curr != cal.begin()) {
      auto prev = --curr;
      // check prev's end time is > start time
      if (prev->second > start)
        return false;
      
    }
    cal.insert({start, end});
    return true;
  }
};

class MyCalendarMap {
  map <int, int> calMap;

  bool canAdd(int maxConflicts) {
    int count = 0;
    for (auto e : calMap) {
      count += e.second;
      if (count > maxConflicts)
        return false;
    }
    return true;
  }

public:
    MyCalendarMap() {   
    }
    
    bool book(int start, int end) {
        calMap[start]++;
        calMap[end]--;
        int maxConflicts = 1;
        if (canAdd(maxConflicts)) {
            return true;
        }
        calMap[start]--;
        calMap[end]++;
        
        return false;
    }
};

void test_set () {
  MyCalendar my;
  bool ret;
  ret = my.book(10, 20); // returns true
  cout << "Start: " << 10 << " End: " << 20 << " Booked:" << ret << endl;

  ret = my.book(15, 25); // returns false
  cout << "Start: " << 15 << " End: " << 25 << " Booked:" << ret << endl;

  ret = my.book(20, 30); // returns true
  cout << "Start: " << 20 << " End: " << 30 << " Booked:" << ret << endl;
}

void test_map () {
  class MyCalendarMap my;
  bool ret;
  ret = my.book(10, 20); // returns true
  cout << "Map : " << endl << "Start: " << 10 << " End: " << 20 << " Booked:" << ret << endl;

  ret = my.book(15, 25); // returns false
  cout << "Start: " << 15 << " End: " << 25 << " Booked:" << ret << endl;

  ret = my.book(20, 30); // returns true
  cout << "Start: " << 20 << " End: " << 30 << " Booked:" << ret << endl;
}

int main () {

  test_set();
  test_map();

  return 0;
}
