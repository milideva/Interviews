#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

bool isAnagram (string s1, string s2) {
  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());
  return s1 == s2;
}

int main () {
  string s1 = "listen";
  string s2 = "silent";
  bool ret;

  ret = isAnagram(s1, s2);
  cout << "S1 :" << s1 << " S2:" << s2 << " isAnagram:" << ret << endl;

  return 0;
}
