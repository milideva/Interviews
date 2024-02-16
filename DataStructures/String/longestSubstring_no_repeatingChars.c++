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
    unordered_map <char, int> char2Index; // Track char to index map
    int l = 0, r = 0;
    int result = 0;
    
    while (r < s.length()) {
      // Find the char in the map
      auto it = char2Index.find(s[r]);
      if (it == char2Index.end()) {
        // char not found, update the max
        result = max(result, r - l + 1);
      } else {
        // char is already seen, move to the next char
        if (char2Index[s[r]] >= l) {
          l = char2Index[s[r]] + 1;
        }
      }
      char2Index[s[r]] = r;
      r++;
    }
    return result;
  }
    
  // Without using map 
  int lengthOfLongestSubstring_2(string s) {        
    int char2Index[128]; // Track char to index map
    int l = 0, r = 0;
    int result = 0;
    
    for (int i = 0; i < 128; ++i) {
      char2Index[i] = -1;
    }

    while (r < s.length()) {
      // Find the char in the map
      auto index = char2Index[s[r]];
      if (index == -1) {
        // char not found, update the max
        result = max(result, r - l + 1);
      } else {
        // char is already seen, move to the next char
        if (index >= l) {
            l = index + 1;
        }
      }
      char2Index[s[r]] = r;
      r++;
    }
    return result;
  }
};

void test (string s) {
  Solution sol;
  int len = sol.lengthOfLongestSubstring(s);
  cout << "String:" << s << " \t\tLongest Substring Without Repeating Characters len:" << len << '\n' ;

  len = sol.lengthOfLongestSubstring_2(s);
  cout << "String:" << s << " \t\tLongest Substring Without Repeating Characters len:" << len << '\n' ;
}

int main (void) {
  Solution sol;
  
  string s1 = "abcabcbb";
  test(s1);

  string s2 = "pwwkew";
  test(s2);

  test("");

  return 0;
}
