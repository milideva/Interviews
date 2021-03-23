/*

  22. Generate Parentheses
  Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:

Input: n = 1
Output: ["()"]

 

Constraints:

    1 <= n <= 8

*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
    void backtrack (vector<string>& res, string curr, int open, int close, int max) {
        if (curr.length() == max * 2) {
            res.push_back(curr);
            cout << curr << '\n';
            return;
        }
        
        if (open < max) 
            backtrack(res, curr + "(", open + 1, close, max);
        if (close < open)
            backtrack(res, curr + ")", open, close + 1, max);
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        backtrack(res, "", 0, 0, n);
        return res;
    }
};

int main ( void ) {
  Solution sol;
  vector <string> ans = sol.generateParenthesis(3);
  return 0;
}
