/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

For example, two is written as II in Roman numeral, just two one's added
together. Twelve is written as, XII, which is simply X + II. The number twenty
seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right.
However, the numeral for four is not IIII. Instead, the number four is written
as IV. Because the one is before the five we subtract it making four. The same
principle applies to the number nine, which is written as IX. There are six
instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: 3
Output: "III"
Example 2:

Input: 4
Output: "IV"
Example 3:

Input: 9
Output: "IX"
Example 4:

Input: 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.
Example 5:

Input: 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map <char,int> umap = {
            {'I',1},
            {'V',5},
            {'X',10},
            {'L',50},
            {'C',100},
            {'D',500},
            {'M',1000}
        };
        int prev = umap[s.back()];
        int ans = 0;
        for (int i = s.size() - 1; i >= 0; i--){
            if (umap[s[i]] < prev) {
                ans -= umap[s[i]];
            } else {
                ans += umap[s[i]];
            }
            prev = umap[s[i]];
        } 
        return ans;
    }
};

string intToRoman(int num) {
  if (num < 1 || num > 3999) 
    return "";
  
  string strArr[] =  {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
  
  int valArr[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  string i2r;
  
  int i = 0;
  while (num && i < size(strArr)) {
    if (valArr[i] > num) {
      i++; continue;
    }
    num = num - valArr[i];
    i2r += strArr[i];
  }
  
  return i2r;
}

void test (int val) {
  Solution sol;
  string str = intToRoman(val);
  cout << "intToRoman " << str << " " << val << endl;
  val = sol.romanToInt(str);
  cout << "romanToInt " << str << " " << val << endl;
}

int main () { 
  Solution sol;
  
  int val = 55;
  test(val);
  val = 585;
  test(val);
  val = 999;
  test(val);

  val = 3949;
  test(val);

  val = 1;
  test(val);

  return 0;
}

