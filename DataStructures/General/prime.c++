#include <vector>
#include <iostream>

using namespace std;

vector <int> generatePrime (void) {
  int cnt = 0;
  const int NUM_PRIMES = 100;
  
  vector <int> res;
  res.reserve(NUM_PRIMES); // Optimization #1 

  int num = 2;

  while (cnt < NUM_PRIMES) {
    
    bool divisible = false;
    
    for (auto i: res) { // // Optimization #2
    //for (int i = 2; i < num; i++) {
      if (num % i == 0) {
        divisible = true;
        break;
      }
      // x^2 > y <--> x <= y^2
      if ((i * i) > num) { // // Optimization # 3
        break;
      }
    } 
    if (divisible == false) {
      res.push_back(num);
      cnt++;
    }
    num++;
  }
  return res;
}

void printVec (vector <int> &vec) {
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << endl;
}

int main (void) {
  vector <int> res = generatePrime();
  printVec(res);

  return 0;
}