/*
93. Restore IP Addresses
A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.

For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.

 
Example 1:

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]
Example 2:

Input: s = "0000"
Output: ["0.0.0.0"]
Example 3:

Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
 

Constraints:

1 <= s.length <= 20
s consists of digits only.

*/

#include <vector>
#include <string>
#include <iostream>


using namespace std;

/*
    Time: O(3^4)
    Space: O(1)
*/

class Solution {
 public:
  vector <string> restoreIpAddresses(const string& s) {
    vector <string> ans;
    vector <string> path;
    dfs(s, 0, path, ans);
    return ans;
  }

 private:
  void dfs(const string& s, int start, vector<string>& path,
           vector<string>& ans) {
    if (path.size() == 4 && start == s.length()) {
      ans.push_back(path[0] + "." + path[1] + "." + path[2] + "." + path[3]);
      return;
    }
    if (path.size() == 4 || start == s.length())
      return;

    for (int length = 1; length <= 3; ++length) {
      if (start + length > s.length())
        return;  // out-of-bounds
      if (length > 1 && s[start] == '0')
        return;  // leading '0'
      const string& num = s.substr(start, length);
      if (stoi(num) > 255)
        return;
      path.push_back(num);
      dfs(s, start + length, path, ans);
      path.pop_back();
    }
  }
};

// Tests for restoreIpAddresses
void test (string s) {
  Solution sol;
  auto out = sol.restoreIpAddresses(s);
  cout << "s: " << s << " \t ip addresses: ";
  for (auto ip : out) {
    cout << ip << " ";
  }
  cout << endl;
}

int main() {
    test("25525511135");
    test("0000");
    test("101023");
    return 0;
}