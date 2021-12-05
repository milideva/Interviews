#include <iostream>
#include <string>

using namespace std;

/* 
   Given a string, find if it's a permutation of a palindrome.
*/

class Solution {

public :
  bool isPermutationOfPalindrome(string str) {

    int count[128] = {0};
    
    for (auto ch : str) {
      if (ch >= 'a' and ch <= 'z') {
	count[ch - 'a']++;
      }
      if (ch >= 'A' and ch <= 'Z') {
	count[ch - 'A']++;
      }
      // ignore non letters
    }

    int maxOdd = 0;
    for (int i = 0; i < 128; i++) {
      if (count[i] % 2) {
	maxOdd++;
      }
      if (maxOdd > 1)
	return false;
    }
    return true;
  }

  bool isPermutationOfPalindrome2 (string str) {
    
    int	count[128] = {0};
    int countOdd = 0;
    
    for	(auto ch : str) {
      int index = -1;
      if (ch >= 'a' and ch <= 'z') {
	index = ch - 'a';
      } else if (ch >= 'A' and ch <= 'Z') {
	index = ch - 'A';
      } else {
	// ignore non letters
	continue;
      }
      count[index]++;
      if (count[index] % 2) {
	countOdd++;
      } else {
	countOdd--;
      }
    }
    return countOdd <= 1;
  }

};

int main () {

  string s = "Tact Coa";
  class Solution sol;
  bool isPP = sol.isPermutationOfPalindrome(s);
  cout << "string: " << s << boolalpha << " isPP: " << isPP << endl;
  s = "Tact Coab";
  isPP = sol.isPermutationOfPalindrome(s);
  cout << "string: " <<	s << boolalpha << " isPP: " << isPP << endl;
  return 0;
}
