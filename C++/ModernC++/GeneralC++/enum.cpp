// g++ enum.cpp -std=c++11

enum OldColor { Red, Blue };
OldColor oc = Red; // Issue1 : pollutes the namespace
int i = oc; // Issue2 : no type safety


/*
  C++11 has introduced enum classes (also called scoped enumerations), that
  makes enumerations both strongly typed and strongly scoped. Class enum doesn’t
  allow implicit conversion to int, and also doesn’t compare enumerators from
  different enumerations.
*/

enum class NewColor { Red, Blue, Magenta };
NewColor nc = NewColor::Magenta;

int j = nc; // does not compile 

int main () {

    return 0;
}
