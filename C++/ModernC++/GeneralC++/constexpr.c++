#include <iostream>

/*
  Constexpr represents expression that is a constant.
  Can apply constexpr to variables or functions! const only for variables
  A compile time constant
  C++17 made constexpr to implicitly mean inline
*/

// Only literal types : void, scalar types (int, float, char, references etc)
constexpr int getNum () {
  return 10;
}

constexpr int add (int a, int b) {
  // can only have simple return statement
  // c++14 allowed conditionals such as if else if etc
  return a + b;
}

constexpr int Max ( int a, int b) {
  return a < b ? a : b;
}

/*
  initialization of const may be deferred till runtime. constexpr init at compile time
*/


int main () {
  constexpr int ceSize = getNum();
  int ceArray[ceSize];

  const int cSize = getNum(); 
  int cArray[cSize]; // Now allowed unless getNum is marked constexpr

  int sum = add ( 3, 8);
  sum = add(ceSize, 9) ;

  sum = add(cSize, 9) ;

  sum = add(sum, 1);

  return 0;
}
