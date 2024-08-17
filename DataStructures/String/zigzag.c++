/*

6. Zigzag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
 

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
Example 3:

Input: s = "A", numRows = 1
Output: "A"
 

Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000

*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        string ans = "";
        vector <string> vecRow(numRows, "");
        int dir = +1;
        int r = 0;
        if (numRows == 1) return s;
        for (int i = 0; i < s.length(); i++) {
            auto ch = s[i];
            vecRow[r] += ch;

            if (r == numRows - 1)
                dir = -1;
            if (r == 0)
                dir = +1;
            r += dir;
        }

        for (int r = 0; r < numRows; r++) {
            ans += vecRow[r];
        }
        return ans;
    }
};

void test_convert() {
    Solution solution;

    // Test Case 1: Example 1 from the problem statement
    string s = "PAYPALISHIRING";
    int numRows = 3;
    string expected = "PAHNAPLSIIGYIR";
    string result = solution.convert(s, numRows);
    assert(result == expected);

    // Test Case 2: Example 2 from the problem statement
    s = "PAYPALISHIRING";
    numRows = 4;
    expected = "PINALSIGYAHRPI";
    result = solution.convert(s, numRows);
    assert(result == expected);

    // Test Case 3: Single character string
    s = "A";
    numRows = 1;
    expected = "A";
    result = solution.convert(s, numRows);
    assert(result == expected);

    // Test Case 4: numRows = 1 (should return the original string)
    s = "HELLO";
    numRows = 1;
    expected = "HELLO";
    result = solution.convert(s, numRows);
    assert(result == expected);

    // Test Case 5: numRows equals the length of the string
    s = "TESTING";
    numRows = 7;
    expected = "TESTING";
    result = solution.convert(s, numRows);
    assert(result == expected);

    // Test Case 6: numRows greater than the length of the string
    s = "SHORT";
    numRows = 10;
    expected = "SHORT";  // Since numRows > s.length(), the string is unchanged
    result = solution.convert(s, numRows);
    assert(result == expected);

    // Test Case 7: A long string with numRows = 2
    s = "ABCDEFGHIJKLMN";
    numRows = 2;
    expected = "ACEGIKMBDFHJLN";
    result = solution.convert(s, numRows);
    assert(result == expected);

    cout << "All test cases passed!" << endl;
}

int main() {
    test_convert();
    return 0;
}