#include <iostream>

// Lambda : 
// Defines an anonymous function object
// syntactic short cut for a functor without having to define a class or struct with operator () overload
// A lambda can be passed to a function that accepts functor as an arg

/* Reasons to use a lambda
   1. Small function : encapsulates few lines of code and can replace function objects
   no need to scroll up / down

   2. No need to create a struct / class for function object

   3. Does not pollute global namespace

   */

// Internally implemented as a nameless function object
/*
  basic lambda 
  []  () {
  
  }
  
  [] is the lambda introducer  and it can contain a capture clause
  ( <args> )
  < mutable >  optional
  < noexcp specification >
  -> < return type > comes after arrow "->"" and may be optional
  {
  
  lambda function body
  }
  
  example 
  
  [] () {
  cout << "Hello Lambda" << endl;
  };
  
  to invoke it
  [] () {
  cout << "Hello Lambda" << endl;
  } () ; // <--- added a call to lambda here
  
  // Give it a name instead of keeping it anonymous
  
  auto fn [] () {
  cout << "Hello Lambda" << endl;
  };
  
  return type is not needed for void, not needed for single type return
  return type is needed if multiple return types are used.

  parts of a lambda:
  1. capture clause (Also known as the lambda-introducer in the C++ specification.)
  
  2. parameter list Optional. (Also known as the lambda declarator)
  
  3. mutable specification Optional.
  
  4. exception-specification Optional.
  
  5. trailing-return-type Optional.
  
  6. lambda body.
  
*/


//Possible compiler's internal implementation of a lambda expression as a function object
template <typename T>

struct Unnamed {
	T operator() (T x, T y) const {
		return x + y;
	}
};

int main () {
  //Compiler automatically creates a function object
  auto fn = []() {
    std::cout << "Welcome to Lambda expressions" << std::endl ;
  };
  
  fn();
  
  std::cout << typeid(fn).name() << std::endl;
  
  //Generic/polymorphic lambda introduced in C++14 - similar to templates!
  
  // g++ -std=c++14 basicLambda.c++

  //				<optional specifiers>
  auto sum = [](auto x, auto y)/*mutable*/ /*noexcept(false) */{
    return x + y;	     //	^^^^		^^^^
  };

  Unnamed<int> n;
  std::cout << "Sum is:" << sum(5.5f, 2.2f) << std::endl;
  
  return 0;
}
