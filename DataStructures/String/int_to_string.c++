#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Integer to English Words
/*

Example 1:

Input: num = 123
Output: "One Hundred Twenty Three"

Example 2:

Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"

Example 3:

Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Example 4:

Input: num = 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"

*/


vector<string> unit1 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
  "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
vector<string> unit2 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

// Handle all 3 digit numbers       
string number2string (int num) {
  string ret;
  if (num >= 100) {
    ret += unit1[num/100] + " Hundred" + " ";
    num = num % 100;
  }
  if (num >= 20) {
    ret += unit2[num/10] + " ";
    num = num % 10;
  }
  if (0<num && num<20)
    ret += unit1[num] + " ";

  return ret;
}
    
string numberToWords(int num) {
  string ret;
  const int billion = 1000000000;
  if (num >= billion) {
    ret += number2string(num/billion) + "Billion" + " ";
    num = num % billion;
  }
  const int million = 1000000;
  if (num >= million) {
    ret += number2string(num/million) + "Million" + " ";
    num = num % million;
  }
  const int thousand = 1000;
  if (num >= thousand) {
    ret += number2string(num/thousand) + "Thousand" + " ";
    num = num % thousand;
  }
  if (num < thousand) {
    ret += number2string(num);
  }
        
  if (ret.empty())
    return "Zero";
  
  return ret.substr(0, ret.size()-1);;
}

void driver (int num) {
  string s = numberToWords(num);
  cout << "Num " << num << " String : " << s << endl;
}
int main () {
  int num = 1232434;
  driver(num);
  num = 100200300;
  driver(num);

  return 0;
}
