/*
Given a string S, check if the letters can be rearranged so that two characters
that are adjacent to each other are not the same.

If possible, output any possible result. If not possible, return the empty
string.

Example 1:

Input: S = "aab"
Output: "aba"

Example 2:

Input: S = "aaab"
Output: ""

Note:
S will consist of lowercase letters and have length in range [1, 500].

*/

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  string reorganizeString(string S) {
    map<char, int> cnts;
    int max = 0;
    for (auto c : S) {
      cnts[c]++;
      max = cnts[c] > max ? cnts[c] : max;
    }
    if (max > (S.length()+1)/2) 
      return "";

    priority_queue <pair<int, char>> pq; // pair <cnt, char>
    for (auto p : cnts)
      pq.push({p.second, p.first});
    
    string res;
    pair<int, char> top1, top2;
    while (!pq.empty()) {
      top1 = pq.top(); pq.pop();
      res += top1.second;
      if (!pq.empty()) {
        res += pq.top().second;
        top2 = pq.top(); pq.pop();
        if (top2.first > 1) 
          pq.push( { top2.first - 1, top2.second } );
      }
      if (top1.first > 1) 
        pq.push( { top1.first - 1, top1.second } );
    }

    return res;
  }
};

int main () {
  string s = "vvvlo";
  class Solution sol;
  string ret = sol.reorganizeString(s);
  cout << "In: " << s << " out: " << ret << endl;
  
  s = "bfrbs";
  ret = sol.reorganizeString(s);
  cout << "In: " << s << " out: " << ret << endl;

  return 0;
}
