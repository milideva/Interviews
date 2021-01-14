#include <iostream>
#include <memory>
#include <vector>

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
