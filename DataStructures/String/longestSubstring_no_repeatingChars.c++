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
    int ans = 0;
    // The substring s[j + 1..i] has no repeating characters.
    int j = -1;
    // lastSeen[c] := the index of the last time char c appeared
    vector<int> lastSeen(128, -1);

    for (int i = 0; i < s.length(); ++i) {
      // Update j to lastSeen[s[i]], so the window must start from j + 1.
      j = max(j, lastSeen[s[i]]);
      ans = max(ans, i - j);
      lastSeen[s[i]] = i;
    }

    return ans;
  }
    
  /*
      Time O(n)
      Space O(128)=O(1)
  */
  // Without using map 
  int lengthOfLongestSubstring_2(string s) {        
    vector <int> count(128);
    int l = 0, r = 0;
    int result = 0;
    
    while (r < s.length()) {
      count[s[r]]++; // unconditionally count current char
      while (count[s[r]] > 1) {
        // this char already exists
        // move from left, until you find the char, decrement all left char count by 1
        count[s[l]]--;
        l++;
      }
      // update max
      result = max(result, r - l + 1);
      r++;
    }
    return result;
  }
};

void test (string s) {
  Solution sol;
  int len = sol.lengthOfLongestSubstring(s);
  cout << "String:" << s << " \t\tlengthOfLongestSubstring() Longest Substring Without Repeating Characters len:" << len << '\n' ;

  len = sol.lengthOfLongestSubstring_2(s);
  cout << "String:" << s << " \t\tlengthOfLongestSubstring_2() Longest Substring Without Repeating Characters len:" << len << '\n' ;
}

int main (void) {
  Solution sol;
  
  string s1 = "abcabcbb";
  test(s1);

  string s2 = "pwwkew";
  test(s2);

  test("");

  // This test case is tricky because t appears first and last and broke earlier code.
  string s3 = "tmmzuxt";
  test(s3);

  return 0;
}
