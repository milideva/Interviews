#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
  1146. Snapshot Array

Implement a SnapshotArray that supports the following interface:

SnapshotArray(int length) initializes an array-like data structure
with the given length.

Initially, each element equals 0.

void set(index, val) sets the element at the given index to be equal
to val.

int snap() takes a snapshot of the array and returns the snap_id: the
total number of times we called snap() minus 1.

int get(index, snap_id) returns the value at the given index, at the
time we took the snapshot with the given snap_id

Example 1:

Input: ["SnapshotArray","set","snap","set","get"]
[[3],[0,5],[],[0,6],[0,0]]
Output: [null,null,0,null,5]
Explanation: 
SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
snapshotArr.set(0,5);  // Set array[0] = 5
snapshotArr.snap();  // Take a snapshot, return snap_id = 0
snapshotArr.set(0,6);
snapshotArr.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5
 

Constraints:

1 <= length <= 50000
At most 50000 calls will be made to set, snap, and get.
0 <= index < length
0 <= snap_id < (the total number of times we call snap())
0 <= val <= 10^9
*/

class Solution {
  vector < unordered_map <int, int> > snapVec;
  int snap_id = -1;

public:
  void SnapshotArray(int length) {
    snapVec = vector < unordered_map <int, int> > (length);
  }
  
  void set(int index, int val) {
    snapVec[index][snap_id] = val;
  }
  
  int snap() {
    snap_id++;
    return snap_id;
  }
  
  int get(int index, int snap_id) {
    int try_snap_id = snap_id - 1;
    while (try_snap_id >= -1){
      // Find previous version
      if (snapVec[index].find(try_snap_id) == snapVec[index].end()) {
	try_snap_id--;
	continue;
      }
      return snapVec[index][try_snap_id];
    }
    return 0;
  }
};


int main () {
  class Solution sol;

  sol.SnapshotArray(3); // set the length to be 3

  sol.set(0,5);  // Set array[0] = 5
  sol.snap();  // Take a snapshot, return snap_id = 0
  sol.set(0,6);
  auto val = sol.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5
  cout << "val : " << val << endl;
  return 0;
}
