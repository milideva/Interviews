#include <queue>
#include <iostream>

using namespace std;

/*

Median is the middle value in an ordered integer list. If the size of the list
is even, there is no middle value. So the median is the mean of the two middle
value.

For example,

[2,3,4], the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

    void addNum(int num) - Add a integer number from the data stream to the data structure.
    double findMedian() - Return the median of all elements so far.

Example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3) 
findMedian() -> 2

Follow up:

    If all integer numbers from the stream are between 0 and 100, how would you optimize it?
    If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?

*/

class MedianFinder {
  priority_queue<int> lo;                              // max heap
  priority_queue<int, vector<int>, greater<int>> hi;   // min heap
  
public:
  void addNum (int num) {
    lo.push(num);                                    // Add to max heap
    hi.push(lo.top());                               // balancing step
    lo.pop();

    if (lo.size() < hi.size()) {                     // maintain size property
      lo.push(hi.top());
      hi.pop();
    }
  }

  double findMedian () {
    return lo.size() > hi.size() ? lo.top() : ((double) lo.top() + hi.top()) * 0.5;
  }
};

int main () {
  class MedianFinder sol;

  sol.addNum(1);
  sol.addNum(2);
  double med = sol.findMedian();
  cout << "Median: " << med << endl;
  sol.addNum(3);
  med = sol.findMedian();
  cout << "Median: " << med << endl;

  return 0;
}
