#include "Integer.h"
#include <vector>

using namespace std;

void display (Integer *ptr) {
  if (!ptr) return;
  cout << ptr->GetValue() << endl;
}

void updateValue (Integer &obj) {
  obj.SetValue (obj.GetValue() * 2 );
}

/* Notes

A smart pointer is a class template that you declare on the stack, and
initialize by using a raw pointer that points to a heap-allocated object. After
the smart pointer is initialized, it owns the raw pointer. This means that the
smart pointer is responsible for deleting the memory that the raw pointer
specifies. The smart pointer destructor contains the call to delete, and because
the smart pointer is declared on the stack, its destructor is invoked when the
smart pointer goes out of scope, even if an exception is thrown somewhere
further up the stack.

A unique_ptr does not share its pointer. It cannot be copied to another
unique_ptr, passed by value to a function, or used in any C++ Standard Library
algorithm that requires copies to be made. A unique_ptr can only be moved. This
means that the ownership of the memory resource is transferred to another
unique_ptr and the original unique_ptr no longer owns it.

*/


unique_ptr<Integer> IntegerFactory (int val) {
  // make_unique needs c++14
  return make_unique<Integer> (val);
}

void IntegerVector() {
    vector <unique_ptr<Integer>> vInts;
    
    // Create a few new unique_ptr<Integer> instances
    // and add them to vector using implicit move semantics.
    vInts.push_back( make_unique <Integer>(55));
    vInts.push_back( make_unique <Integer>(555));
    vInts.push_back( make_unique <Integer>(5555));
    vInts.push_back( make_unique <Integer>(55555));

    // Pass by const reference when possible to avoid copying.
    for (const auto& i : vInts) {
      display(i.get());
    }    
}

void test (int val) {

  // Declare a smart pointer on stack and pass it the raw pointer
  // declaration does not need a "*" 
  std::unique_ptr<Integer> uPtr(new Integer(val));
  
  if (uPtr == nullptr) {
    uPtr.reset(new Integer(val));
  }

  uPtr->SetValue(val * 2);

  // Smart pointers usually provide a way to access their raw pointer directly.
  // You may pass the raw pointer to code that does not support smart pointers.
  // C++ Standard Library smart pointers have a get member function for this
  // purpose

  display(uPtr.get());

  // Pass a reference to a method.
  updateValue(*uPtr);

  // Smart pointers have a reset member function that releases ownership of the
  // pointer. This is useful when you want to free the memory owned by the smart
  // pointer before the smart pointer goes out of scope
  uPtr.reset();

  
  auto iu1 = IntegerFactory(777);
  display(iu1.get());

  auto iu2 = move(iu1);
  display(iu2.get());
  
  display(iu1.get()); // Damn this still works, 

} // smart pointer automatically deleted here

int main () {
  test(100);
  return 0;
}


