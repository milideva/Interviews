
#include <iostream>
#include <vector>
using namespace std;
/*
    43. Multiply Strings

    Given two non-negative integers num1 and num2 represented as strings, 
    return the product of num1 and num2, also represented as a string.

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

class Solution {
    // First multiply a string with a digit
    string multiply (string num, int dig, int zeroes) {
        int n = 0;
        int carry = 0;
        string s = "";
        for (int i = num.size() - 1; i >= 0; i--) {
            n = (num[i] - '0') * dig + carry;
            s += to_string(n%10);
            carry = n / 10;
        }
        if (carry)
            s += to_string(carry);
        while (zeroes--) 
            s = "0" + s;
        reverse(s.begin(), s.end());
        return s;
    }

    // add strings
    string addString (string a, string b) {
        if (a.size() == 0) return b;
        if (b.size() == 0) return a;
        int sz1 = a.size();
        int sz2 = b.size();
        string res;
        int carry = 0;
        vector <int> v;
        while (sz1 or sz2) {
            int sum = 0;
            if (sz1) {
                sz1--;
                sum +=  a[sz1] - '0';
            }
            if (sz2) {
                sz2--;
                sum += b[sz2] - '0';
            }
            sum += carry;
            v.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry) {
            v.push_back(carry);
        }
        for (auto n:v) {
            res = to_string(n) + res ;
        }
        return res;
    }

    /*
                 123
    *            123
    ----------------
                 369 = "123" * "3"
                2460 = "123" * "2" + "0"        
               12300 = "123" * "1" + "00"       -> multiply(string s, int digit, int zeroes): return s '*' multiple + zero * '0'
    -----------------
               15129 = "369"+"2460"+"12300"   -> addString(string, string): return string '+' string
           */
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        int sz2 = num2.size();
        
        int zeroes = 0;
        vector <string> vec;
        while (sz2) {
            unsigned char ch2 = num2[sz2-1];
            string s = multiply(num1, ch2 - '0', zeroes);
            zeroes++;
            sz2--;
            vec.push_back(s);
        }
        string sum = "";
        for (auto s : vec) {
            sum = addString(s, sum);
        }
        return sum;
    }
};

void test (string num1, string num2, string expected) {
    Solution sol;
    string res = sol.multiply(num1, num2); 
    cout << "num1 * num2 : " << num1 << " * " << num2 << " = " << res << " \t expected:" << expected << endl;
}

int main(void)
{

    test("2", "3", "6");
    test("123", "456", "56088");
    
    return 0;
}
