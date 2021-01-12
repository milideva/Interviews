#include "Integer.h"
#include <iostream>

/* Notes

move is always applied to l-value
simply performs a type cast to r-value reference 
when object is moved, it goes into unspecified state but you can reinit it and reuse it

Rule of five

Because the presence of a user-defined destructor, copy-constructor, or
copy-assignment operator prevents implicit definition of the move constructor
and the move assignment operator, any class for which move semantics are
desirable, has to declare all five special member functions.

Applications of move
- Unique pointer
- Non-copiable objects such as file stream
*/

Integer Add (const Integer &a, const Integer &b) {
  Integer temp ;
  temp.SetValue(a.GetValue() + b.GetValue());
  return temp ;
}

int main() {
  Integer a(1), b(3) ;
  a.SetValue(Add(a,b).GetValue());

  Integer c = 5; // ~ Integer c = Integer(5) but compiler's copy ellision optimization avoid temp copy

  auto d(static_cast <Integer &&> (c)); // this will move, but is ugly and does not convey the intend to move
  
  auto e { std::move(a) }; // This is heavily used for unique pointers , do not use a now to read since internal state has moved

  e = std::move(c);

  return 0;
}
