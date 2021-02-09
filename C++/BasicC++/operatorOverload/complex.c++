#include "complex.h"

Complex *createComplex (int r, int i) {
  Complex *c = new Complex {r, i};
  return c;
}

void test_smartPtr (void) {
  std::shared_ptr<Complex> shPtr{ createComplex(5, 10) };
  if (shPtr == nullptr) {
    shPtr.reset(new Complex {5, 10} );
  }
  shPtr->display();
  shPtr.reset();
}



int main () {

  Complex c1 {5, 2}, c2 { 15, 12 }, c3 { 25, 22 };

  Complex temp = c1 + c2 + c3;

  temp.display();

  return 0;
}
