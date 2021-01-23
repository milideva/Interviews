
/*
  The C++ Standard defines a set of attributes and also allows compiler vendors
  to define their own attributes (within a vendor-specific namespace), but
  compilers are required to recognize only those attributes defined in the
  standard.

  Attributes represent a standardized alternative to vendor-specific extensions
  such as #pragma directives, __declspec() (Visual C++), or __attribute__ (GNU).
  However, you will still need to use the vendor-specific constructs for most
  purposes.

  examples :

  * [[noreturn]] Specifies that a function never returns; in other words it
  always throws an exception. The compiler can adjust its compilation rules for
  [[noreturn]] entities.

  * [[nodiscard]] (with /std:c++17) Specifies that a function's return value is
  not intended to be discarded
*/


// C++14 feature

[[deprecated]] 
int f() {
  return 0;
}

[[deprecated("g() is thread-unsafe. Use h() instead")]]
void g ( int& x ) {

}

void h ( int& x ) {

}

void test() {
  int a = f(); // warning: 'f' is deprecated  [-Wdeprecated-declarations]
  g(a); // warning: 'g' is deprecated: g() is thread-unsafe. Use h() instead  [-Wdeprecated-declarations]
}
int main () {
  test();
  return 0;
}
