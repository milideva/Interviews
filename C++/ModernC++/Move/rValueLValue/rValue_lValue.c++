#include <iostream>

//Returns r-value
int Add (int x, int y) {
  return x + y;
}

//Return l-value
int & Transform (int &x) {
  x *= x;
  return x;
}

void Print (int &x) {
  std::cout << "Print(int&)" << std::endl; 
}

void Print (const int &x) {
  std::cout << "Print(const int&)" << std::endl;  
}

void Print (int &&x) {
  std::cout << "Print(int &&)" << std::endl;
}

/*

* l-value
- all variables are l-value
- can be assigned a value
- has a name
- functions that return by reference
= l-value reference to l-value only (except it can reference to a const r-value)

• r-value 
- R-value is a temporary value
- can not be assigned a value
- has no name
- functions that return by value
- r-values reference to r-value

R-value Reference && 
always binds to temporary, can not bind to l-value
Used to implement move!

*/

int main() {
  //x is lvalue
  int x = 10;
  
  //ref is l-value reference
  int &ref = x ;
  
  //Transform returns an l-value
  int &ref2 = Transform(x) ;
  
  //Binds to function that accepts l-value reference
  Print(x);
  
  //rv is r-value reference
  int &&rv = 8 ;
  
  //Add returns a temporary (r-value)
  int &&rv2 = Add(3,5) ;
  
  //Binds to function that accepts a temporary, i.e. r-value reference
  Print(3);

  return 0;
}

