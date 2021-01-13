#include <memory>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;


/*
  Sometimes an object must store a way to access the underlying object of a
  shared_ptr without causing the reference count to be incremented. Typically,
  this situation occurs when you have cyclic references between shared_ptr
  instances.

  The best design is to avoid shared ownership of pointers whenever you can.
  However, if you must have shared ownership of shared_ptr instances, avoid
  cyclic references between them. When cyclic references are unavoidable, or
  even preferable for some reason, use weak_ptr to give one or more of the
  owners a weak reference to another shared_ptr. By using a weak_ptr, you can
  create a shared_ptr that joins to an existing set of related instances, but
  only if the underlying memory resource is still valid. A weak_ptr itself does
  not participate in the reference counting, and therefore, it cannot prevent
  the reference count from going to zero. However, you can use a weak_ptr to try
  to obtain a new copy of the shared_ptr with which it was initialized. If the
  memory has already been deleted, the weak_ptr's bool operator returns false.
  If the memory is still valid, the new shared pointer increments the reference
  count and guarantees that the memory will be valid as long as the shared_ptr
  variable stays in scope.

*/

class Printer {
  weak_ptr <int> wPtr {};

public :

  void setValue (weak_ptr <int> wp) {
    wPtr = wp;
  }

  void Print () {
    if (wPtr.expired()) {
      cout << "Weak Pointer points to expired resource" << endl;
      return;
    }
    auto sharedPtr = wPtr.lock(); // this returns the shared pointer and increments its ref count
    cout << "Value: " << *sharedPtr << endl;
    cout << "Ref Count: " << sharedPtr.use_count() << endl;
  }
  
  ~Printer () {
    //cout << __FUNCTION__ << endl;
  }
};

int main () {
  Printer prn;

  srand(time(0));
  
  int num = rand() % 100;
  shared_ptr <int> sp { new int {num}};
  
  prn.setValue(sp);
  cout << "random int : " << num << endl;
  if (*sp > 50) {
    sp = nullptr;
  }
  prn.Print();
  
  return 0;
}
