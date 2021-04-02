
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
