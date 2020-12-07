#include <iostream>
#include <vector>
#include <map>
#include <queue>

/*

Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words
have the same frequency, then the word with the lower alphabetical order comes
first.

Example 1:

Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.

Example 2:

Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.

Note:

    You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
    Input words contain only lowercase letters.

*/

using namespace std;

struct comp {
  bool operator () (pair <string, int>& a, pair <string, int>& b ) {
    if (a.second > b.second) return true;
    if (a.second == b.second) return a.first < b.first;
    return false;
  }
};
    
vector<string> topKFrequent(vector<string>& words, int k) {
  map <string, int> mywords;
  
  for (auto w : words)
    mywords[w]++;
  
  // minHeap of count -> string
  priority_queue < pair<string, int>, vector <pair <string, int>>, comp>  pq;
  
  for (auto w : mywords) {
    pq.push(w);
    if (pq.size() > k) {
      pq.pop(); // throw away the smallest at the top of minHeap
    }
  }
  
  vector <string> res;
  while (!pq.empty()) {
    auto n = pq.top();
    pq.pop();
    res.push_back(n.first);
  }
  reverse(res.begin(), res.end());
  return res;
}


int main () {
  
  vector <string> s = { "the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"};

  vector <string> ans = topKFrequent(s, 4);
  
  for (auto v : ans) {
    cout << " " << v ;
  }
  cout << endl;
  return 0;
}

