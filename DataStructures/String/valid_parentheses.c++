/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.

 

Example 1:

Input: s = "()"
Output: true

Example 2:

Input: s = "()[]{}"
Output: true

Example 3:

Input: s = "(]"
Output: false

Example 4:

Input: s = "([)]"
Output: false

Example 5:

Input: s = "{[]}"
Output: true

 

Constraints:

    1 <= s.length <= 104
    s consists of parentheses only '()[]{}'.

*/
#include <string>
#include <stack>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isValid (string s) {
        stack <char> stk;
        for (int i = 0; i < s.length(); i++) {
            char ch = s[i];
            switch (ch) {
                case '{':
                    stk.push(ch);
                    break;
                case '}':
                    if (stk.empty() || stk.top() != '{')
                        return false;
                    stk.pop();
                    break;
                case '[':
                    stk.push(ch);
                    break;
                case ']':
                     if (stk.empty() || stk.top() != '[')
                         return false;
                    stk.pop();
                    break;
                case '(':
                    stk.push(ch);
                    break;
                case ')':
                    if (stk.empty() || stk.top() != '(')
                         return false;
                    stk.pop();
                    break;
                default:
                    break;
            }
        }
        if (!stk.empty()) 
            return false;
        return true;
    }
};

int main () {
  class Solution sol;
  string s = "{[]}";

  bool res = sol.isValid(s);

  cout << "string:: " << s << endl << "isValid:: " << res << endl;

  return 0;
}

