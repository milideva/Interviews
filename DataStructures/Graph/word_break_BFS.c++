/*

139. Word Break
Medium

Given a string s and a dictionary of strings wordDict, return true if s can be
segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the
segmentation. 

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false

*/

#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        
        unordered_set <string> dictSet (wordDict.begin(), wordDict.end());

        vector<bool> visited (s.length(), false);
        
        queue <int> q;
        q.push(0);
        
        while (!q.empty()) {
            int i = q.front(); q.pop();
            if (visited[i])
                continue;
            
            for (int j = i + 1; j <= s.length(); j++) {
                string sub = s.substr(i, j - i);
                if (dictSet.count(sub) != 0) {
                    q.push(j);
                    if (j == s.length()) {
                        return true;
                    }
                }
            }
            visited[i] = true;
        }
        
        return false;
    }
};


int main (void) {

  Solution sol;

  vector <string> vec = { "leet", "code" };

  bool ret = sol.wordBreak("leetcode", vec);
  cout << "leetcode wordBreak ret:" << ret << '\n';

  vector <string> vec2 = { "apple","pen" };
  ret = sol.wordBreak("applepenapple", vec2);
  cout << "applepenapple wordBreak ret:" << ret << '\n';

  vector <string> vec3 = {"cats","dog","sand","and","cat"};
  ret = sol.wordBreak("catsandog", vec3);
  cout << "catsandog  wordBreak ret:" << ret << '\n';

  return 0;
}
