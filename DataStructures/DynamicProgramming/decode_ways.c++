#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26

Given a non-empty string containing only digits, determine the total number of ways to decode it.

The answer is guaranteed to fit in a 32-bit integer.

 

Example 1:

Input: s = "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).

Example 2:

Input: s = "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Example 3:

Input: s = "0"
Output: 0
Explanation: There is no character that is mapped to a number starting with '0'.
We cannot ignore a zero when we face it while decoding. So, each '0' should be
part of "10" --> 'J' or "20" --> 'T'.

Example 4:

Input: s = "1"
Output: 1

*/

class Solution {

public:
    int numDecodings(string s) {
        int len = s.length();
        if (!len) return 0;
        int prev = 1;
        int prev2, curr;
        
        for (int i = len-1; i >= 0; i--) {
            if (s[i] == '0') {
                curr = 0;
            } else {
                curr = prev;
            }
            
            if (i == len-1) {
                prev2 = prev;
                prev = curr;
                continue;
            }

            if (s[i] == '1' || (s[i] == '2' && s[i+1] < '7')) {
                curr += prev2;
            }
            prev2 = prev;
            prev = curr;
        }
        return prev;
    }
};

int main () {
  class Solution sol;
  string str = "12";
  int count = sol.numDecodings(str);
  cout << "str:" << str << " #ways:" << count << endl;
  
  str = "27";
  count = sol.numDecodings(str);
  cout << "str:" << str << " #ways:" << count << endl;
  
  str = "1234";
  count = sol.numDecodings(str);
  cout << "str:" << str << " #ways:" << count << endl;
  
  
  return 0;
}
