#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// g++ -std=c++17 top_freq_numbers_stream.c++

/*

703. Kth Largest Element in a Stream

Design a class to find the kth largest element in a stream. Note that
it is the kth largest element in the sorted order, not the kth
distinct element.

Implement KthLargest class:

KthLargest(int k, int[] nums) Initializes the object with the integer
k and the stream of integers nums.

int add(int val) Appends the integer val to the stream and returns the
element representing the kth largest element in the stream.

*/

/* The issue here is if you use a maxHeap, then to get kth max, you
   must pop k times and then save those and then push again k times,
   this will kill the performance. The idea here is to use minHeap.
*/ 

/*
Example 1:

Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output
[null, 4, 5, 5, 8, 8]

Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8
*/

class KthLargest {
    int k;
    priority_queue <int, vector<int>, greater<int> > pq; // minHeap
public:
  KthLargest(int kin, vector<int>& nums) {
    k = kin;
    for (auto n : nums) {
      add(n);
    }
  }
  
  int add (int val) {
    
    if (pq.size() < k) {
      pq.push(val);
    } else {
      if (pq.top() < val) {
	pq.pop();
	pq.push(val);
      }
    }
    cout << "kth largest : " << pq.top() << " k: " << k << endl;
    return pq.top();
  }
};


int main () {
  vector <int> nums = { 4, 5, 8, 2 };
  auto k = 3;
  
  KthLargest sol(k, nums);
  
  auto n = sol.add(4);

  n = sol.add(5);

  n = sol.add(5);

  n = sol.add(8);
  n = sol.add(8);
  
  return 0;
}

