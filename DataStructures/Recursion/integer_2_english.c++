#include <iostream>
#include <string>

/*
    273. Integer to English words
*/
using namespace std;

class Solution {

    vector <string> under20 = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

    vector <string> tens = { "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    string helper (long num) {
        if (num < 20) 
            return under20.at(num);
        if (num < 100) 
            return tens.at(num / 10) + " " + under20.at(num % 10);
        if (num < 1000) 
            return helper(num / 100) + " " + "Hundred" + " " + helper(num % 100);
        if (num < 1000000) 
            return helper(num / 1000) + " " + "Thousand" + " " + helper(num % 1000);
        if (num < 1000000000) 
            return helper(num / 1000000) + " " + "Million" + " " + helper(num % 1000000);
        return helper(num / 1000000000) + " " + "Billion" + " " + helper(num % 1000000000);
    }

public:
    string num2words(long num) {

        if (num == 0) return "zero";
        return helper(num);
    }
};

void test (long num) {
    Solution sol;
    auto out = sol.num2words(num);
    cout << "num: " << num << " \t english: " << out << endl;
}

int main() {
    test(0);
    test(15);
    test(35);
    test(569);
    test(1232);
    test(42424);
    test(947891);
    test(3447891);
    test(13947891);
    test(567947891);
    test(9567947891);
    return 0;
}