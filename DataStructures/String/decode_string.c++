/*
394. Decode String


Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the
square brackets is being repeated exactly k times. Note that k is guaranteed to
be a positive integer.

You may assume that the input string is always valid; No extra white spaces,
square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits
and that digits are only for those repeat numbers, k. For example, there won't
be input like 3a or 2[4].


Example 1:

Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:

Input: s = "3[a2[c]]"
Output: "accaccacc"

Example 3:

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"

Example 4:

Input: s = "abc3[cd]xyz"
Output: "abccdcdcdxyz"

Constraints:

    1 <= s.length <= 30
    s consists of lowercase English letters, digits, and square brackets '[]'.
    s is guaranteed to be a valid input.
    All the integers in s are in the range [1, 300].

*/

#include <stack>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    string decodeString(string s) {
        if (s.empty()) 
            return s;
        
        stack <int> cntStk;
        stack <string> strStk;
        
        int index = 0;
        string res = "";
        while (index < s.length()) {
            // Only 4 possibilities, a digit or [ or ] or a char
            if (isdigit(s[index])) {
                
                int num = 0;
                while (isdigit(s[index]))  {
                    num = num * 10 + s[index] - '0';
                    index++;
                }
                cntStk.push(num);                       
            } else if (s[index] == '[') {
                // A new string starts, push the old one
                strStk.push(res);
                index++;
                res = "";
            } else if (s[index] == ']') {
                string out = strStk.top(); strStk.pop();
                int k = cntStk.top(); cntStk.pop();
                while (k--)
                    out += res;
                res = out;
                index++;
            } else {
                res = res + s[index];
                index++;
            }
        }
        return res;
    }
};

int main () {
  class Solution sol;
  string in = "2[abc]3[cd]ef";
  string out;

  out = sol.decodeString(in);
  cout << "in: " << in << " decoded out: " << out << endl;
  return 0;
}
