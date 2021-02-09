#include <iostream>
#include <memory>
#include <vector>

/*

Exceptions versus assertions

Exceptions and asserts are two distinct mechanisms for detecting run-time errors
in a program. 

Use assert statements to test for conditions during development that should
never be true if all your code is correct. There's no point in handling such an
error by using an exception, because the error indicates that something in the
code has to be fixed. It doesn't represent a condition that the program has to
recover from at run time. An assert stops execution at the statement so that you
can inspect the program state in the debugger.

An exception continues execution from the first appropriate catch handler. Use
exceptions to check error conditions that might occur at run time even if your
code is correct, for example, "file not found" or "out of memory." Exceptions
can handle these conditions, even if the recovery just outputs a message to a
log and ends the program. 

Always check arguments to public functions by using exceptions. Even if your
function is error-free, you might not have complete control over arguments that
a user might pass to it.
*/

class A {
public:
  A() {
    std::cout << "A()" << std::endl;
  }
  ~A() {
    std::cout << "~A()" << std::endl;
  }
};

class B {
public:
  B() {
    std::cout << "B()" << std::endl;
  }
  ~B() {
    std::cout << "~B()" << std::endl;
  }
};

class Test {
  std::unique_ptr<A> pA{};
  B b{};
  std::unique_ptr<int> pInt{};
  std::string pStr{};
  std::vector<int> pArr{};
public:
  Test() { 
    std::cout << "Test():Acquire resources" << std::endl;
    pA.reset(new A);
    
    /*pA = new A;
      pInt = new int;
      pStr = new char[1000];
      pArr = new int[50000];
      // Memory allocated via new will leak if constructor throws an exception
      // new can throw exception if out of memory.
      // Solution ? RAII !  Use smart pointers instead.
    */

    throw std::runtime_error("Failed to initialize"); 
  }
  
  ~Test() {  
    std::cout << "~Test():Release resources" << std::endl; 
    //throw std::runtime_error("Failed to initialize");
    // A destructor should not throw an exception
    // because a destructor could get called during stack unwinding due to an exception
    // and in such a case, a program will terminate and can not catch during stack unwinding.

    /*delete pA;
      delete pInt;
      delete[]pStr;
      delete[] pArr;*/
  }
};

int main() {
  try {
    Test t;
    throw std::runtime_error{ "Exception" };
  }
  catch (std::runtime_error &ex) {
    std::cout << ex.what() << std::endl;
  }
  return 0;
}
