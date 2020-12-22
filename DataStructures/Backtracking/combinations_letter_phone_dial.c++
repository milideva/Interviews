/*

Given a string containing digits from 2-9 inclusive, return all possible letter
combinations that the number could represent. Return the answer in any order.

A mapping of digit to letters (just like on the telephone buttons) is given
below. Note that 1 does not map to any letters.

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:

Input: digits = ""
Output: []

Example 3:

Input: digits = "2"
Output: ["a","b","c"]

 

Constraints:

    0 <= digits.length <= 4
    digits[i] is a digit in the range ['2', '9'].

*/
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
  vector <string> d2l;
  vector <string> res;
  string path;
  
  void dfs (string digits, int pos) {
    if (pos == digits.size()) {
      res.push_back(path);
      return;
    }
    
    for (auto ch : d2l[digits[pos] - '0'] ) {
      path.push_back(ch);
      dfs(digits, pos + 1);
      path.pop_back();
    }
  }
    
public:
  Solution () {
    d2l = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
  }
  
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) return res;
    
    dfs(digits, 0);
    return res; 
  }
};

int main () {
  class Solution sol;
  vector <string> res;
  string dig = "23";
  res = sol.letterCombinations(dig);
  cout << "Digits:" << dig << endl;
  cout << "Combinations:" ;
  for (auto s : res) {
    cout << s << " ";
  }
  cout << endl;
  return 0;
}
