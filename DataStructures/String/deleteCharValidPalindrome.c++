/*

680. Valid Palindrome II

Given a string s, return true if the s can be palindrome after deleting at most one character from it.

Example 1:

Input: s = "aba"
Output: true
Example 2:

Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
Example 3:

Input: s = "abc"
Output: false
 

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters.

*/

#include <string>
#include <cassert>

using namespace std;

class Solution {
    bool checkPalindrome (string s, int start, int end) {
        while (start <= end) {
            if (s[start] != s[end])
                return false;
            start++;
            end--;
        }
        return true;
    }
public:
    bool validPalindrome(string s) {
        int start = 0;
        int end = s.length() - 1;

        while (start <= end) {
            if (s[start] == s [end]) {
                start++;
                end--;
                continue;
            }
            return checkPalindrome(s, start+1, end) || checkPalindrome(s, start, end-1);
        }
        return true;
    }
};

int main() {

    Solution sol;

    string s1 = "abca";
    assert(sol.validPalindrome(s1) == true && "s1 is not a palindrome!");

    string s2 = "abc";
    assert(sol.validPalindrome(s2) == false && "s2 is a palindrome!");

    return 0;
}