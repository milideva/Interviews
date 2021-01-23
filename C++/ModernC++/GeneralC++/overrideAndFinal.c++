/*

  The override keyword serves two purposes:
  
  It shows the reader of the code that "this is a virtual method, that is
  overriding a virtual method of the base class."
  
  The compiler also knows that it's an override, so it can "check" that you are
  not altering/adding new methods that you think are overrides.

*/


class base {
public:
  virtual int foo(float x) = 0; 
};


class derived: public base {
public:
  int foo(float x) override { ... } // OK
}

class derived2: public base {
public:
  int foo(int x) override { ... } // ERROR
};

// In derived2 the compiler will issue an error for "changing the type". Without
// override, at most the compiler would give a warning for "you are hiding
// virtual method by same name".


/*

  Sometimes you don’t want to allow derived class to override the base class’
  virtual function. C++ 11 allows built-in facility to prevent overriding of
  virtual function using final specifier.

  2nd use of final specifier: final specifier in C++ 11 can also be used to
  prevent inheritance of class / struct. If a class or struct is marked as final
  then it becomes non inheritable and it cannot be used as base class/struct.

*/


#include <iostream>
using namespace std;
 
class Base {
public:
  virtual void myfun() final {
    cout << "myfun() in Base";
  }
};

class Derived : public Base {
  void myfun() {
    cout << "myfun() in Derived\n";
  }
};

/* Wont compile

error: virtual function ‘virtual void Derived::myfun()’
     void myfun()
          ^
error: overriding final function ‘virtual void Base::myfun()’
     virtual void myfun() final 
*/
 
int main() {
    Derived d;
    Base &b = d;
    b.myfun();
    return 0;
}


