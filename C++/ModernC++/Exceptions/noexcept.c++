#include <iostream>

/* Applied to functions in both declaration and definition
   Indicates tha the function does not throw exception
   Compiler can optimise the function code - no need to generate stack unwinding code.
   An exception by such a function, will terminate the program and stack may not be unwind.ed

   noexcept(true) or just noexcept - means does not throw exception
*/
void Test (int x) noexcept(false) {
  // calling a library function such as cout, don't mark noexcept
  std::cout << x << std::endl;
  //throw x;
}

// Inherits exception specification of Test(x) 
int Sum (int x, int y) noexcept( noexcept( Test(x) )) {
  Test(x);
  return x + y;
}

class A {
public:
  //Destructors are implicitly noexcept(true) in C++11
  ~A() {
    throw 3; 
  }
};

int main() {
  A a;
  //boolalpha manipulator prints 0 & 1 as false & true

  // Destructors should not throw, they are implicitly noexcept
  std::cout << std::boolalpha << noexcept(a.~A()) << std::endl;

  // also user defined classes, if they immplement move constructor and move assignment, mark them noexcept

  try {
    Sum(3, 5);
    //Other statements
  }
  catch (int x) {
    std::cout << x << std::endl ;
  }
  return 0;
}
