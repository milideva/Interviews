
/*

Given a string s of '(' , ')' and lowercase English characters. 

Your task is to remove the minimum number of parentheses ( '(' or ')', in any
positions ) so that the resulting parentheses string is valid and return any
valid string.

Formally, a parentheses string is valid if and only if:

    It is the empty string, contains only lowercase characters, or
    It can be written as AB (A concatenated with B), where A and B are valid strings, or
    It can be written as (A), where A is a valid string.

 

Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

Example 2:

Input: s = "a)b(c)d"
Output: "ab(c)d"

Example 3:

Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.

Example 4:

Input: s = "(a(b(c)d)"
Output: "a(b(c)d)"
*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  string minRemoveToMakeValid(string s) {
    // Mark extra ( as a *, in going from front to end of the string
    int opening = 0;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(')
        opening++;
      else if(s[i] == ')')
        opening--;
      if (opening < 0) {
        s[i] = '*'; 
        opening++;
      }
    }
    // Mark extra ) as a *, in going from end to front of the string
    int closing = 0;
    for (int i = s.size() -1; i >= 0; i--) {
      if (s[i] == '(')
        closing--;
      else if (s[i] == ')')
        closing++;
      if (closing < 0) {
        s[i] = '*';
        closing++;
      }
    }
    auto s1 = remove(s.begin(), s.end(), '*');
    
    s.erase(s1, s.end());
    return s;
  }
};

int main () {
  class Solution sol;
  string s = "a)b(c)d";
  string res;

  res = sol.minRemoveToMakeValid(s);  

  cout << "string:: " << s << endl << "out:: " << res << endl;

  return 0;
}
