
/*

Given a string s containing just the characters '(', ')', '{', '}',
'[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:

Input: s = "()"
Output: true
Example 2:

Input: s = "()[]{}"
Output: true
Example 3:

Input: s = "(]"
Output: false
 

Constraints:

1 <= s.length <= 104
s consists of parentheses only '()[]{}'

*/

#include <stack>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
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


int main (void) {

  Solution sol;
  string str = "()[]{}";

  bool ret = sol.isValid(str);
  cout << "str: " << str << " valid:" << ret << endl;

  return 0;
}
