
/*

We have a list of points on the plane.  Find the K closest points to the origin (0, 0).

(Here, the distance between two points on a plane is the Euclidean distance.)

Example 1:

Input: points = [[1,3],[-2,2]], K = 1
Output: [[-2,2]]
Explanation: 
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].

Example 2:

Input: points = [[3,3],[5,-1],[-2,4]], K = 2
Output: [[3,3],[-2,4]]
(The answer [[-2,4],[3,3]] would also be accepted.)

*/

#include <iostream>
#include <vector>

using namespace std;

struct pt_compare {
  bool operator() (vector<int>& p1, vector<int>& p2) {
    return (p1[0]*p1[0] + p1[1]*p1[1]) > (p2[0]*p2[0] + p2[1]*p2[1]);
  }
};

vector <vector<int>> kClosest (vector<vector<int>>& points, int K) {
  vector <vector<int>> ans;

/*
  Optimization to reduce the size of heap, keep it of size K only 
  sort(points.begin(), points.end(), pt_compare());
  points.erase(points.begin() + K, points.end());
*/

  // make heap, works on a vector, just rearranges vector elements
  // default is max heap, supply your own func to compare
  // pt_compare must be supplied for every 'heap' operation on the heap

  // Supply a "greater" function that returns true for 'greater'
  // This is to build a "minHeap" - top K elements of minHeap are closest

  make_heap(points.begin(), points.end(), pt_compare());
  
  while (K) {

    pop_heap(points.begin(), points.end(), pt_compare() );

    // Pop_heap only moves it to the end of vector
    // the old top of heap is at the back of vector, copy it
    ans.push_back(points.back());

    // remove old top of heap, back of vector
    points.pop_back();

    K--;
  }
  
  return ans;
}

void print_point (vector <int> v) {
  cout << "( " << v[0] << ", " << v[1] << " ) ";
}

int main () {
  
  vector <vector <int>> points = { {6, -2}, {3, 3}, {5, -1}, {-2, 4}, {5, 3} };

  vector <vector <int>> ans = kClosest(points, 2);
  
  for (auto v : ans) {
    print_point(v);
  } 
  cout << endl;
  return 0;
}
