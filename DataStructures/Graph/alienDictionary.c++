#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

using namespace std;

/*

There is a new alien language that uses the English alphabet. However,
the order among the letters is unknown to you.

You are given a list of strings words from the alien language's
dictionary, where the strings in words are sorted lexicographically by
the rules of this new language.

Return a string of the unique letters in the new alien language sorted
in lexicographically increasing order by the new language's rules. If
there is no solution, return "". If there are multiple solutions,
return any of them.

A string s is lexicographically smaller than a string t if at the
first letter where they differ, the letter in s comes before the
letter in t in the alien language. If the first min(s.length,
t.length) letters are the same, then s is smaller if and only if
s.length < t.length.

Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Example 2:

Input: words = ["z","x"]
Output: "zx"
Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".
 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of only lowercase English letters.
*/

class Solution {
  
  unordered_map <char, int> inDegree; // char->numCharsBefore
  unordered_map <char, vector<char>> graph;
  string result = "";
  
  bool buildGraph(vector<string>& words) {
    for (auto w : words) {
      for (auto c: w) {
	inDegree[c] = 0;
	graph[c] = vector<char>();
      }
    }
    
    for (int i = 0; i < words.size() - 1; i++) {
      auto w1 = words[i];
      auto w2 = words[i+1];
      if (w1.length() > w2.length() && w1.find(w2) == 0) {
	return false;
      }
      // char after common len, can not have ordering
      auto commonLen = min(w1.length(), w2.length());
      
      for (int j = 0; j < commonLen; j++) {
	auto parentCh = w1[j];
	auto childCh = w2[j];
        
	if (parentCh != childCh) {
	  // First different character within commonLength
	  // parentCh comes before childCh
	  graph[parentCh].push_back(childCh);
	  // someone is before childCh
	  inDegree[childCh]++;
	  // no further ordering
	  break;
	}
      }
    }
    
    return true;
  }
  
  void bfsTopoSort(void) {
    queue <char> q;
    for (auto [ch, count]: inDegree) {
      if (count == 0) {
	q.push(ch);
      }
    }
        
    while (!q.empty()) {
      auto vertex = q.front(); q.pop();
      result += vertex;
      // decrement the indegree for each child as we are removing the source vertex
      for (auto child : graph[vertex]) {
	inDegree[child]--;
	if (inDegree[child] == 0) {
	  q.push(child);
	}
      }
    }
    
    if (result.size() != inDegree.size()) 
      result = "";
  }
  
public:
  string alienOrder(vector<string>& words) {
    
    bool ret = buildGraph(words);
    
    if (ret == false) 
      return result; // something went wrong in ordering
    
    bfsTopoSort();
    return result;
  }
};


int main () {

  class Solution sol;

  vector <string> words {"wrt","wrf","er","ett","rftt"};

  auto res = sol.alienOrder(words);

  cout << "Alien Dictionary : ";
  for (auto w : words) {
    cout << w << " ";
  }

  cout << endl << "Alien Order : " << res << endl;
  
  return 0;
}
