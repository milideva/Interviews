#include <iostream>
#include <string>

using namespace std;

/* String to integer */
class Solution {
    void trim (string &s) {
        s.erase(0, s.find_first_not_of(' '));
        s.erase(s.find_last_not_of(' ') + 1);
    }

public:
    int my_atoi (string s) {
        trim(s);
        if (s.empty())
            return 0;
        int sign = s[0] == '-' ? -1 : 1;
        if (s[0] == '+' || s[0] == '-') {
            s = s.substr(1);
        }
        long long num = 0;

        for (char c : s) {
            if (isdigit(c) == false) {
                break;
            }
            int n = c - '0';
            num = num * 10 + n;
        }

        return sign * num;
    }
    
};

void test (string str) {
    Solution sol;

    int n = sol.my_atoi(str);

    cout << "str:" << str << " atoi: " << n << endl;
}

int main (void) {
    test("  -123 ");
    test("   +524  ");

    return 0;
}