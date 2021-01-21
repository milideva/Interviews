#include "Integer.h"
#include <iostream>

/* Notes

move is always applied to l-value

std::move performs an unconditional cast to an rvalue reference. 
In and of itself, it doesn’t move anything.

std::forward casts its argument to an rvalue only if that argument is bound to
an rvalue.

Neither std::move nor std::forward do anything at runtime.

When an object is moved, it goes into unspecified state but you can reinit it
and reuse it.

There are thus several scenarios in which C++11’s move semantics do you no good:
• No move operations: The object to be moved from fails to offer move opera‐
tions. The move request therefore becomes a copy request. 

• Move not faster: The object to be moved from has move operations that are no
faster than its copy operations.

• Move not usable: The context in which the moving would take place requires a
move operation that emits no exceptions, but that operation isn’t declared noex
cept.


*/

/*

  The official name for "universal reference" is now forwarding reference.
  std::move performs an unconditional cast to an rvalue.
  std::forward casts its argument to an rvalue only if that argument is bound to an rvalue.

  Those are two very different actions. The first one typically sets up a move,
  while the second one just passes—forwards—an object to another function in a
  way that retains its original lvalueness or rvalueness.

  how std::forward can know whether its argument was initialized with an rvalue?

  That information is encoded in template parameter T, that parameter is passed
  to std::forward, which recovers the encoded information.

*/

/*
move semantics
○ based on rvalue references
○ an rvalue is a temporary object which is going to be destroyed at
the end of an expression
○ In older C++, rvalues only bind to const references
○ C++11 allows non-const rvalue references, which are references to
an rvalue objects
○ since an rvalue is going to die at the end of an expression, you can
steal its data
○ instead of copying it into another object, you move its data into
another object
*/

/*
Rule of five

Because the presence of a user-defined destructor, copy-constructor, or
copy-assignment operator prevents implicit definition of the move constructor
and the move assignment operator, any class for which move semantics are
desirable, has to declare all five special member functions.

*/

/* 
   Universal references

   auto&& var2 = var1; // not rvalue reference

   template<typename T> 
   void f(T&& param); // not rvalue reference

   “T&&” has two different meanings. One is rvalue reference, of course. 


   The other meaning for “T&&” is either rvalue reference or lvalue reference.
   Such references look like rvalue references in the source code (i.e.,
   “T&&”), but they can behave as if they were lvalue references (i.e., “T&”).
   Their dual nature permits them to bind to rvalues (like rvalue references) as
   well as lvalues (like lvalue references). Furthermore, they can bind to const
   or non-const objects, to volatile or non-volatile objects, even to objects
   that are both const and volatile. They can bind to virtually any‐ thing. Such
   unprecedentedly flexible references may be called universal references.


   Universal references arise in two contexts. The most common is function
   template parameters. The second context is auto declarations.
   What these contexts have in common is the presence of type deduction.

   Because universal references are references, they must be initialized. The
   initializer for a universal reference determines whether it represents an
   rvalue reference or an lvalue reference.

   Summary:

   • If a function template parameter has type T&& for a deduced type T, or if
     an object is declared using auto&&, the parameter or object is a universal
     refer‐ ence.

   • If the form of the type declaration isn’t precisely type&&, or if type
     deduction does not occur, type&& denotes an rvalue reference.
   
   • Universal references correspond to rvalue references if they’re initialized
     with rvalues. They correspond to lvalue references if they’re initialized
     with lval‐ ues.


 */

/*
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
