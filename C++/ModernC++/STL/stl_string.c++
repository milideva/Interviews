#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef>        // std::size_t

using namespace std;

void test_find_first_of () {
  string str ("Please, replace the vowels in this sentence by asterisks. 27th Nov" );
  size_t found = str.find_first_of("aeiou");
  cout << "Original string:" << str << endl;
  while (found!=string::npos) {
    str[found]='*';
    found=str.find_first_of("aeiou",found+1);
  }

  cout << "After aeiou to * using find_first_of():" << str << '\n';


  size_t pos = str.find_first_of("0123456789");
  string numStr;

  if (pos != string::npos) 
    numStr = str.substr(pos);
  cout << "numStr:" << numStr << endl;
}

void test_substr () {
  string str = "This is a beautiful day! 27th Nov";
  string sub = str.substr(10, 9);
  size_t pos = str.find("is");
  string posStr = str.substr(pos);

  cout << "Original:" << str << endl;
  cout << "sub:" << sub << endl;
  cout << "from pos:" << pos << " rest str:" << posStr << endl;
}

// s = "1111 2222 3333"

void test_parse_space_str () {
  string s = "1111 2222 3333";

  int pos1 = s.find(' ');
  int pos2 = s.rfind(' ');

  string str1 = s.substr(0, pos1);
  string str2 = s.substr(pos1 + 1, pos2 - pos1 - 1);

  cout << "str1:" << str1 << " str2:" << str2 << endl;
}

int main () {

  test_substr();
  test_find_first_of();
  test_parse_space_str();

  return 0;
}
