#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

bool isAlpha (string s) {
  return all_of(s.begin(), s.end(), ::isalpha);
}

void toLower (string &str) {
  transform(str.begin(), str.end(), str.begin(), ::tolower);
}

bool isAnagram2 (string s1, string s2) {
  int l1 = s1.length();
  int l2 = s2.length();
  
  if (l1 != l2) return false;

  if (isAlpha(s1) == false) return false;
  if (isAlpha(s2) == false) return false;
  
  toLower(s1);
  toLower(s2);

  vector <int> count1(26, 0);
  vector <int> count2(26, 0);
  
  for (auto i = 0; i < l1; i++) {
    count1[s1[i] - 'a']++;
    count2[s2[i] - 'a']++;
  }
  return count1 == count2;
}

bool isAnagram (string s1, string s2) {
  sort(s1.begin(), s1.end());
  sort(s2.begin(), s2.end());
  return s1 == s2;
}

int main () {
  string s1 = "listen";
  string s2 = "silent";
  string s3;
  bool ret;

  ret = isAnagram(s1, s2);
  cout << "S1 :" << s1 << " S2:" << s2 << " isAnagram():" << ret << endl;

  ret = isAnagram2(s1, s2);
  cout << "S1 :" << s1 << " S2:" << s2 << " isAnagram2():" << ret << endl;

  ret = isAnagram2(s1, s3);
  cout << "S1 :" << s1 << " S3:" << s3 << " isAnagram2():" << ret << endl;

  return 0;
}
