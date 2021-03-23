/*

1047. Remove All Adjacent Duplicates In String

Given a string S of lowercase letters, a duplicate removal consists of choosing
two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made. It is
guaranteed the answer is unique.

 

Example 1:

Input: "abbaca"
Output: "ca"
Explanation: 

For example, in "abbaca" we could remove "bb" since the letters are adjacent and
equal, and this is the only possible move. The result of this move is that the
string is "aaca", of which only "aa" is possible, so the final string is "ca".


*/

#include <string>
#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    string removeDuplicates (string S) {
        stack <char> stk;
        string res;
        
        for (auto ch: S) {
            if (stk.size() == 0) {
                stk.push(ch);
                res.push_back(ch);
                continue;
            }
            char prev = stk.top();
            if (prev == ch) {
                stk.pop();
                res.pop_back();
                continue;
            }
            stk.push(ch);
            res.push_back(ch);
        }
        return res;
    }
};


int main (void) {

  Solution sol;
  string str = "pbbcggttciiippooaais";
  string ans = sol.removeDuplicates(str);

  cout << "In:" << str << " out:" << ans << '\n';
  
  str = "deeedbbcccbdaa";
  ans = sol.removeDuplicates(str);
  cout << "In:" << str << " out:" << ans << '\n';
  
  str = "abbaca";
  ans = sol.removeDuplicates(str);
  cout << "In:" << str << " out:" << ans << '\n';
  

  return 0;
}
