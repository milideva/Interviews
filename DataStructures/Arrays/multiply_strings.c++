/*

43. Multiply Strings

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

 

Example 1:

Input: num1 = "2", num2 = "3"
Output: "6"
Example 2:

Input: num1 = "123", num2 = "456"
Output: "56088"
 

Constraints:

1 <= num1.length, num2.length <= 200
num1 and num2 consist of digits only.
Both num1 and num2 do not contain any leading zero, except the number 0 itself.

*/

#include <vector>
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
    typedef unsigned long long ull;

    ull s2n (string s) {
        ull n = 0;
        for (int i = 0; i < s.length(); i++) {
            n = n * 10 + s[i] - '0';
        }
        return n;
    }
    string n2s(unsigned long long n) {
        string s;
        string dig = "0123456789";
        if (!n) return "0";
        while (n) {
            int d = n % 10;
            s = dig[d] + s;
            n = n / 10;
        }
        return s;
    }

public:
    /*
    string multiply(string num1, string num2) {
        unsigned long long prod = s2n(num1) * s2n(num2);
        return n2s(prod);

        // This does not work for big numbers
        // "498828660196" * "840477629533" overflows
        // expected "419254329864656431168468"
    }
    */

    string multiply(string num1, string num2) {

        if (num1 == "0" || num2 == "0") return "0";
        
        // num1.size() + num2.size() == max no. of digits
        vector<int> num(num1.size() + num2.size(), 0);
        
        /*
                2 1 0   Index
                1 2 3   num1
            *   4 5 6   num2
        ===============
        
        Explanation : Neetcode video https://www.youtube.com/watch?v=1vZswirL8Y8
        */
        // build the number by multiplying one digit at the time
        for (int i = num1.size() - 1; i >= 0; --i) {
            for (int j = num2.size() - 1; j >= 0; --j) {

                num[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
                num[i + j] += num[i + j + 1] / 10;
                num[i + j + 1] %= 10;
            }
        }
        
        // skip leading 0's
        int i = 0;
        while (i < num.size() && num[i] == 0) ++i;
        
        // transofrm the vector to a string
        string res = "";
        while (i < num.size()) 
            res.push_back(num[i++] + '0');
        
        return res;
    }
};

void test_multiply() {
    Solution sol;

    // Test case 1: Simple multiplication
    assert(sol.multiply("2", "3") == "6");

    // Test case 2: Multiplication involving zero
    assert(sol.multiply("0", "123456789") == "0");
    assert(sol.multiply("123456789", "0") == "0");

    // Test case 3: Multiplying single digit numbers
    assert(sol.multiply("9", "9") == "81");

    // Test case 4: Multiplying large numbers
    assert(sol.multiply("123456789", "987654321") == "121932631112635269");

    // Test case 5: Multiplying different lengths of numbers
    assert(sol.multiply("123", "4567") == "561741");

    // Test case 6: Multiplying with carries
    assert(sol.multiply("99", "99") == "9801");

    // Test case 7: Multiplying numbers with leading zeros
    assert(sol.multiply("000123", "456") == "56088");

    // Test case 8: Edge case with single-digit results
    assert(sol.multiply("1", "1") == "1");

    // Test case 9: Both numbers are large
    assert(sol.multiply("498828660196", "840477629533") == "419254329864656431168468");

    std::cout << "All test cases passed!\n";
}

int main() {
    test_multiply();
    return 0;
}