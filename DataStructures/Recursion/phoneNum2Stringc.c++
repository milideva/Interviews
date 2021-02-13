
#include <vector>
#include <iostream>
using namespace std;

/*
  Given a string str representing digits of a phone numbeere, write a program to
  return all the possible letter combinations that the number could represent.
*/

class Solution {
  
  vector <string> num2Str = { 
    "",  /* 0 */
    "",  /* 1 */
    "abc", /* 2 */
    "def", /* 3 */
    "ghi", /* 4 */
    "jkl", /* 5 */
    "mno", /* 6 */
    "pqrs",/* 7 */
    "tuv", /* 8 */
    "wxyz",/* 9 */
  };
  
  vector <string> solve (string& number, int currIndex) {
    if (currIndex >= number.length()) {
      return {};
    }
    vector <string> getAll = solve(number, currIndex+1);

    string currDigStr = num2Str[number[currIndex] - '0'];
    vector <string> ans;

    if (currDigStr.size() == 0) {
      // digits 0 and 1 have no characters
      return getAll;
    }
    for (auto c : currDigStr) {
      if (getAll.size() == 0) {
        string s;
        s += c;
        ans.push_back(s);
        continue;
      }
      for (auto str : getAll) {
        string s(str);
        s += c;
        ans.push_back(s);
      }
    }
    return ans;
  }

public:
  
  vector <string> combinations (string number) {
    return solve(number, 0);
  }  
};

int main (void) {
  
  Solution sol;
  
  vector <string> ans = sol.combinations("3124");
  
  for (auto s: ans) {
    cout << s << " " << endl;
  }
  return 0;
}


/*
Complexity Analysis:  

Time Complexity: O(4n), where n is a number of digits in the input number. 

Each digit of a number has 3 or 4 alphabets, so it can be said that each digit
has 4 alphabets as options. If there are n digits then there are 4 options for
the first digit and for each alphabet of the first digit there are 4 options in
the second digit, i.e for every recursion 4 more recursions are called (if it
does not match the base case). So the time complexity is O(4n).

Space Complexity:O(1). 
As no extra space is needed.

*/
