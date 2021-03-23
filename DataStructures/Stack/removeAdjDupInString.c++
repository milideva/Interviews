/*

  1209. Remove All Adjacent Duplicates in String II

Given a string s, a k duplicate removal consists of choosing k adjacent and
equal letters from s and removing them causing the left and the right side of
the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made.

It is guaranteed that the answer is unique.
 

Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.

Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"

Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"

*/

#include <string>
#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack <int> counts;
        
        for (int i = 0; i < s.size(); i++) {
            if (i == 0) {
                counts.push(1);
                continue;
            }
            if (s[i] != s[i-1]) {
                counts.push(1);
                continue;
            }
            int cnt = counts.top(); counts.pop();
            cnt++;
            if (cnt == k) {
                s.erase(i - k + 1,  k);
                i = i - k;
            } else {
                counts.push(cnt);
            }   
        }
        return s;
    }
};


int main (void) {

  Solution sol;
  int k = 2;
  string str = "pbbcggttciiippooaais";
  string ans = sol.removeDuplicates(str, k);

  cout << "In:" << str << " k:" << k << " out:" << ans << '\n';
  
  str = "deeedbbcccbdaa";
  k = 3;
  ans = sol.removeDuplicates(str, k);
  cout << "In:" << str << " k:" << k << " out:" << ans << '\n';
  
  return 0;
}
