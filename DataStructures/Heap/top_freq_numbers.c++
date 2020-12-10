#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;
// g++ -std=c++17 top_freq_numbers.c++

vector<int> topKFrequent (vector<int>& nums, int k) {
  unordered_map <int, int> mymap; // number --> count
  for (auto i : nums) {
    mymap[i]++;
  }
  
  priority_queue <pair<int, int>> pq; // default is max Heap, priority based on first element
  
  for (auto [n,c] : mymap) {
    pq.push( {c, n}); // pair's first is count c, second is number n
  }
  
  vector <int> res;
  while (k) {
    auto [c, n] = pq.top();
    pq.pop();
    res.push_back(n);
    k--;
  }
  return res;
}


int main () {
  
  vector <int> nums = { 6, 3, -2, 3, 3, 5, 3, 7, 5, -1, 7, -1, -2, 4, -1, 5, 3 };
  
  vector <int> ans = topKFrequent(nums, 5);
  
  for (auto v : ans) {
    cout << " " << v ;
  }
  cout << endl;
  return 0;
}

