#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) {
  unordered_map <int, int> mymap; // number --> count
  for (auto i : nums) {
    mymap[i]++;
  }
  
  priority_queue <pair<int, int>> pq;
  
  for (auto i : mymap) {
    pq.push(make_pair(i.second, i.first));
  }
  
  vector <int> res;
  while (k) {
    int n = pq.top().second;
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

