#include <string>
#include <cassert>
#include <iostream>

using namespace std;

/* 
    You are given a binary string s (a string containing only "0" and "1"). You may choose up to one "0" and flip it to a "1". 
    What is the length of the longest substring achievable that contains only "1"?

    For example, given s = "1101100111", the answer is 5. If you perform the flip at index 2, the string becomes 1111100111.
*/

int findLength (string s) {

    int maxLen, l, r, zeroes;
    l = maxLen = zeroes = 0;
    for (r = 0; r < s.length(); r++) {
        if (s[r] == '0') {
            zeroes++;
            while (zeroes > 1 and l <= r) {
                if (s[l] == '0')  {
                    zeroes--;
                }
                l++;
            }
        }   
        maxLen = max(maxLen, r - l + 1);
    }
    return maxLen;
}

void testFindLength() {
    // Test case 1
    string s1 = "1101100111";
    int expected1 = 5;
    int result1 = findLength(s1);
    cout << "Test case 1: expected = " << expected1 << ", got = " << result1;
    cout << (result1 == expected1 ? " -> passed!" : " -> failed!") << endl;

    // Test case 2
    string s2 = "1111";
    int expected2 = 4;
    int result2 = findLength(s2);
    cout << "Test case 2: expected = " << expected2 << ", got = " << result2;
    cout << (result2 == expected2 ? " -> passed!" : " -> failed!") << endl;

    // Test case 3
    string s3 = "0000";
    int expected3 = 1;
    int result3 = findLength(s3);
    cout << "Test case 3: expected = " << expected3 << ", got = " << result3;
    cout << (result3 == expected3 ? " -> passed!" : " -> failed!") << endl;

    // Test case 4
    string s4 = "101010";
    int expected4 = 3;
    int result4 = findLength(s4);
    cout << "Test case 4: expected = " << expected4 << ", got = " << result4;
    cout << (result4 == expected4 ? " -> passed!" : " -> failed!") << endl;

    // Test case 5
    string s5 = "110100110";
    int expected5 = 4;
    int result5 = findLength(s5);
    cout << "Test case 5: expected = " << expected5 << ", got = " << result5;
    cout << (result5 == expected5 ? " -> passed!" : " -> failed!") << endl;

    // Test case 6: Edge case with empty string
    string s6 = "";
    int expected6 = 0;
    int result6 = findLength(s6);
    cout << "Test case 6: expected = " << expected6 << ", got = " << result6;
    cout << (result6 == expected6 ? " -> passed!" : " -> failed!") << endl;

    // Test case 7: Edge case with one character '0'
    string s7 = "0";
    int expected7 = 1;
    int result7 = findLength(s7);
    cout << "Test case 7: expected = " << expected7 << ", got = " << result7;
    cout << (result7 == expected7 ? " -> passed!" : " -> failed!") << endl;

    // Test case 8: Edge case with one character '1'
    string s8 = "1";
    int expected8 = 1;
    int result8 = findLength(s8);
    cout << "Test case 8: expected = " << expected8 << ", got = " << result8;
    cout << (result8 == expected8 ? " -> passed!" : " -> failed!") << endl;
}

int main() {
    testFindLength();
    return 0;
}