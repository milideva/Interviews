/*

3. Longest Substring Without Repeating Characters
Given a string s, find the length of the longest substring without repeating characters.
 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Example 4:

Input: s = ""
Output: 0

*/

#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(string s) {        
    unordered_map <char, int> charMap;
    int start = -1;
    int maxLen = 0;
    
    for (int i = 0; i < s.size(); i++) {
      if (charMap.count(s[i]) != 0) {
        start = max(start, charMap[s[i]]);
      }
      charMap[s[i]] = i;
      maxLen = max(maxLen, i - start);
    }
    
    return maxLen;
  }
};

int main (void) {
  Solution sol;
  
  string s1 = "abcabcbb";
  
  int len = sol.lengthOfLongestSubstring(s1);
  cout << "String:" << s1 << " len:" << len << '\n' ;
  
  string s2 = "pwwkew";
  len = sol.lengthOfLongestSubstring(s2);
  cout << "String:" << s2 << " len:" << len << '\n' ;
  
  return 0;
}
