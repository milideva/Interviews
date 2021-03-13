/*

159. Longest Substring with At Most Two Distinct Characters
Medium

Given a string s, return the length of the longest substring that contains at
most two distinct characters.

Example 1:

Input: s = "eceba"
Output: 3
Explanation: The substring is "ece" which its length is 3.

Example 2:

Input: s = "ccaabbb"
Output: 5
Explanation: The substring is "aabbb" which its length is 5.

*/

#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        
        unordered_map <char, int> ht; // char to count hash table
        int left, right;
        left = right = 0;
        
        int size = s.length();
        int ans = 0;
        
        while (right < size) {
            char rch = s[right];
            ht[rch]++;
            
            if (ht.size() > 2) {
                while (ht.size() > 2 && left < right) {
                    char lch = s[left];
                    ht[lch]--;
                    if (ht[lch] == 0) {
                        ht.erase(lch);
                    }
                    left++;
                }
            }
            
            ans = max(ans, right - left + 1);
            right++;
        }
        return ans;
    }
};

int main (void) {
  Solution sol;

  string s1 = "eceba";
  int len = sol.lengthOfLongestSubstringTwoDistinct(s1);
  cout << "String:" << s1 << " lengthOfLongestSubstringTwoDistinct:" << len << '\n' ;

  string s2 = "ccaabbb";
  len = sol.lengthOfLongestSubstringTwoDistinct(s2);
  cout << "String:" << s2 << " lengthOfLongestSubstringTwoDistinct:" << len << '\n' ;

  return 0;
}
