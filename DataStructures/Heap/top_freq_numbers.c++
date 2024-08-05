#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;
// g++ -std=c++17 top_freq_numbers.c++

/*
347. Top K Frequent Elements

Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

 

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique

*/

vector<int> topKFrequent (vector<int>& nums, int k) {
  unordered_map <int, int> num2cnt; // number --> count
  for (auto i : nums) {
    num2cnt[i]++;
  }
  
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

  for (auto [n,c] : num2cnt) {
    // pq.push( {c, n}); // pair's first is count c, second is number n
    // Do not push all elements otherwise it is log n
    // maintain only k elements in the heap, so as to get log k, that's why we used minHeap.
    if (minHeap.size() < k) {
      minHeap.push({c, n});
      continue;
    }
    auto [topC, topN] = minHeap.top();
    if (c < topC) {
        continue; // no need to insert
      }
    minHeap.pop(); // remove the top
    minHeap.push({c, n}); // insert the new element
  }
  /* More readable : 
  for (auto [n, c] : num2cnt) {
    if (minHeap.size() < k) {
      minHeap.push({c, n});
    } else if (c > minHeap.top().first) {
      minHeap.pop();
      minHeap.push({c, n});
    }
  }

  */

  
  vector <int> res;
  while (k) {
    auto [c, n] = minHeap.top();
    minHeap.pop();
    res.push_back(n);
    k--;
  }
  return res;
}

bool compareResults(vector<int> result, vector<int> expected) {
    sort(result.begin(), result.end());
    sort(expected.begin(), expected.end());
    if (result != expected) {
        cout << "Result: ";
        for (int num : result) {
            cout << num << " ";
        }
        cout << "\nExpected: ";
        for (int num : expected) {
            cout << num << " ";
        }
        cout << endl;
        return false;
    }
    return true;
}

int main() {
    vector<pair<vector<int>, pair<int, vector<int>>>> tests = {
        {{1, 1, 1, 2, 2, 3}, {2, {1, 2}}},
        {{1}, {1, {1}}},
        {{1, 1, 1, 1, 1}, {1, {1}}},
        {{1, 1, 2, 2, 3, 3}, {2, {1, 2}}},
        {{1, 2, 3, 4, 5}, {3, {1, 2, 3}}},
        {{1, 2, 2, 3, 3, 3, 4, 4, 4, 4}, {4, {4, 3, 2, 1}}},
        {{1, 2, 2, 3, 3, 3}, {3, {1, 2, 3}}},
        {{}, {0, {}}}
    };

    for (int i = 0; i < tests.size(); i++) {
        auto [nums, p] = tests[i];
        auto [k, expected] = p;
        vector<int> result = topKFrequent(nums, k);
        if (compareResults(result, expected)) {
            cout << "Test " << i + 1 << " passed." << endl;
        } else {
            cout << "Test " << i + 1 << " failed." << endl;
        }
    }

    return 0;
}