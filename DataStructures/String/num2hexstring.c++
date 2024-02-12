/*

405. Convert a Number to Hexadecimal

Given an integer num, return a string representing its hexadecimal representation. For negative integers, two’s complement method is used.

All the letters in the answer string should be lowercase characters, and there should not be any leading zeros in the answer except for the zero itself.

Note: You are not allowed to use any built-in library method to directly solve this problem.

 

Example 1:

Input: num = 26
Output: "1a"
Example 2:

Input: num = -1
Output: "ffffffff"
 

Constraints:

-231 <= num <= 231 - 1


*/


#include <string>
#include <iostream>

using namespace std;

class Solution {
    const string HEX="0123456789abcdef";
public:
    string toHex(int num) {
        string s = "";
        int count = 0;
        if (!num) return "0";
        while    (num && count++ < 8) {
            int n = num & 0xf;
            s = HEX[n] + s;
            num = num >> 4;
        }
        return s;
    }
};


int main() {
    Solution sol;

    int num = 26;
    string out = sol.toHex(num);
    cout << "num: " << num << " hex string:" << out << endl;

    num = -1;
    out = sol.toHex(num);
    cout << "num: " << num << " hex string:" << out << endl;

    return 0;
}