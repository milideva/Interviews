/*

340. Longest Substring with At Most K Distinct Characters

Given a string s and an integer k, return the length of the longest substring of
s that contains at most k distinct characters.

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.

Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.

Constraints:

    1 <= s.length <= 5 * 104
    0 <= k <= 50

*/

#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:

  int lengthOfLongestSubstringKDistinct(string s, int k) {
    unordered_map <char, int> ht;
    int l = 0, r = 0;
    
    int maxlen = 0;
    while (r < s.size()) {
      ++ht[s[r]];
      if (ht.size() <= k) 
        maxlen = max(r - l + 1, maxlen);
      if (ht.size() > k) {  
        char lch = s[l];
        if (--ht[lch] <= 0)
          ht.erase(lch);
        ++l;
      }
      ++r;
    }
    return maxlen;
  }
};

int main (void) {
  Solution sol;

  string s1 = "eceba";
  int len = sol.lengthOfLongestSubstringKDistinct(s1, 2);
  cout << "String:" << s1 << " lengthOfLongestSubstringKDistinct:" << len << '\n' ;

  string s2 = "aa";
  len = sol.lengthOfLongestSubstringKDistinct(s2, 1);
  cout << "String:" << s2 << " lengthOfLongestSubstringKDistinct:" << len << '\n' ;

  return 0;
}
