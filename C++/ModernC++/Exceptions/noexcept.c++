#include <iostream>

/* 
   Applied to functions in both declaration and definition
   Indicates tha the function does not throw exception
   Compiler can optimise the function code - no need to generate stack unwinding code.
   An exception by such a function, will terminate the program and stack may not be unwind.ed
   
   noexcept(true) or just noexcept - means does not throw exception
*/

/*

  Exceptions and performance

  The exception mechanism has a minimal performance cost if no exception is
  thrown. If an exception is thrown, the cost of the stack traversal and
  unwinding is roughly comparable to the cost of a function call. Additional
  data structures are required to track the call stack after a try block is
  entered, and additional instructions are required to unwind the stack if an
  exception is thrown. However, in most scenarios, the cost in performance and
  memory footprint isn't significant. The adverse effect of exceptions on
  performance is likely to be significant only on memory-constrained systems.
  Or, in performance-critical loops, where an error is likely to occur regularly
  and there's tight coupling between the code to handle it and the code that
  reports it. In any case, it's impossible to know the actual cost of exceptions
  without profiling and measuring. Even in those rare cases when the cost is
  significant, you can weigh it against the increased correctness, easier
  maintainability, and other advantages that are provided by a well-designed
  exception policy.
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
