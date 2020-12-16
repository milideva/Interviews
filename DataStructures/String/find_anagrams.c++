#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*

Given a string s and a non-empty string p, find all the start indices of p's
anagrams in s.

Strings consists of lowercase English letters only and the length of both
strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

*/
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sl = s.length();
        int pl = p.length();
        vector <int> res;
        if (sl < pl) return res;
        
        vector<int> sCountArr(26, 0);
        vector<int> pCountArr(26,0);
        
        for (int i = 0; i < pl; i++) {
            pCountArr[p[i] - 'a']++;
            sCountArr[s[i] - 'a']++;
        }
        if (sCountArr == pCountArr)
            res.push_back(0);        
        for (int i = pl; i < sl; i++) {
            sCountArr[s[i] - 'a']++;
            sCountArr[s[i-pl] - 'a']--;
            if (sCountArr == pCountArr)
                res.push_back(i-pl+1);
        }
        return res;
    }
};

int main () {
  class Solution sol;
  string s = "abab";
  string p = "ab";
  
  vector <int> res;

  res = sol.findAnagrams(s, p);  

  cout << "string:" << s << " search:" << p << endl;
  for (auto i : res) {
    cout << i  << " " ; 
  }
  cout << endl;

  s= "cbaebabacd"; p = "abc";

  res = sol.findAnagrams(s, p);  
  cout << "string:" << s << " search:" << p << endl;
  for (auto i : res) {
    cout << i  << " " ; 
  }
  cout << endl;

  return 0;
}
