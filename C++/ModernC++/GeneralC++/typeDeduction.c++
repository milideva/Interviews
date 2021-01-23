
// 1. template type deduction

/*
  pseudocode:
  template<typename T> 
  void f(ParamType param);
  // A call :
  f(expr);

  Compilers use expr to deduce two types: one for T and one for ParamType. These
  types are frequently different, because ParamType often contains adornments,
  e.g., const or reference qualifiers.

  The type deduced for T is dependent not just on the type of expr, but also on
  the form of ParamType. There are three cases:

  Case 1
  ParamType is a pointer or reference type, but not a universal reference. 

  Case 2
  ParamType is a universal reference. 

  Case 3
  ParamType is neither a pointer nor a reference.


  Case 1
  ParamType is a Reference or Pointer, but not a Universal Reference
  1. If expr’s type is a reference, ignore the reference part.
  2. Then pattern-match expr’s type against ParamType to determine T.
  For example, if this is our template,
  template<typename T>
  void f(T& param); // param is a reference
  int x = 27;
  const int cx = x;
  const int& rx = x; // rx is a reference to x as a const int

  the deduced types for param and T in various calls are as follows:
  f(x); // T is int, param's type is int&
  f(cx); // T is const int, param's type is const int&
  f(rx); // T is const int, param's type is const int&

  In the second and third calls, notice that because cx and rx designate const
  values, T is deduced to be const int, thus yielding a parameter type of const
  int&. That’s important to callers. When they pass a const object to a reference
  parameter, they expect that object to remain unmodifiable, i.e., for the
  parameter to be a reference-to- const. That’s why passing a const object to a
  template taking a T& parameter is safe: the constness of the object becomes part
  of the type deduced for T.

  In the third example, note that even though rx’s type is a reference, T is
  deduced to be a non-reference. That’s because rx’s reference-ness is ignored
  during type deduc‐ tion.


  Case 2

  Things are less obvious for templates taking universal reference parameters.
  Such parameters are declared like rvalue references (i.e., in a function
  template taking a type parameter T, a universal reference’s declared type is
  T&&), but they behave differ‐ ently when lvalue arguments are passed in.

  • If expr is an lvalue, both T and ParamType are deduced to be lvalue
    references. That’s doubly unusual. First, it’s the only situation in
    template type deduction where T is deduced to be a reference. Second,
    although ParamType is declared using the syntax for an rvalue reference, its
    deduced type is an lvalue reference.

    • If expr is an rvalue, the “normal” (i.e., Case 1) rules apply. 

    For example:
    template<typename T> 
    void f(T&& param);      // param is now a universal reference

    int x = 27; 
    const int cx = x;
    const int& rx = x;
    f(x);  // x is lvalue, so T is int&,  param's type is also int&
    f(cx); // cx is lvalue, so T is const int&, param's type is also const int&
    f(rx); // rx is lvalue, so T is const int&, param's type is also const int&
    f(27); // 27 is rvalue, so T is int, param's type is therefore int&&


    The key point here is that the type deduction rules for universal reference
    parameters are different from those for parameters that are lvalue
    references or rvalue references.

    Case 3
    ParamType is Neither a Pointer nor a Reference

    When ParamType is neither a pointer nor a reference, we’re dealing with pass-by-value:

    template<typename T>
    void f(T param); // param is now passed by value

    That means that param will be a copy of whatever is passed in—a completely
    new object. The fact that param will be a new object motivates the rules
    that govern how T is deduced from expr:

    1. As before, if expr’s type is a reference, ignore the reference part.

    2. If, after ignoring expr’s reference-ness, expr is const, ignore that,
    too. If it’s volatile, also ignore that.

    int x = 27;
    const int cx = x;
    const int& rx = x;

    f(x); // T's and param's types are both int
    f(cx); // T's and param's types are again both int
    f(rx); // T's and param's types are still both int

    Note that even though cx and rx represent const values, param isn’t const. 

    param is an object that’s completely independent of cx and rx—a copy of cx
    or rx. The fact that cx and rx can’t be modified says nothing about whether
    param can be. That’s why expr’s constness (and volatileness, if any) is
    ignored when deducing a type for param: just because expr can’t be modified
    doesn’t mean that a copy of it can’t be.


    Things to Remember

    • During template type deduction, arguments that are references are treated
    as non-references, i.e., their reference-ness is ignored.
      
    • When deducing types for universal reference parameters, lvalue arguments get
    special treatment.

    • When deducing types for by-value parameters, const and/or volatile argu‐
    ments are treated as non-const and non-volatile.

    • During template type deduction, arguments that are array or function names
    decay to pointers, unless they’re used to initialize references.

*/



// 2. auto 

/*
  Internally, auto type deduction is template type deduction.

  • auto type deduction is usually the same as template type deduction, but auto
    type deduction assumes that a braced initializer represents a std::initial
    izer_list, and template type deduction doesn’t.

  • auto in a function return type or a lambda parameter implies template type
    deduction, not auto type deduction.

*/


// 3. decltype

/* 
   The decltype type specifier yields the type of a specified expression. The
   decltype type specifier, together with the auto keyword, is useful primarily
   to developers who write template libraries. Use auto and decltype to declare
   a template function whose return type depends on the types of its template
   arguments. Or, use auto and decltype to declare a template function that
   wraps a call to another function, and then returns the return type of the
   wrapped function.
*/


void test () {
  int   i;
  int&& f();
  auto          x3a = i;     // decltype(x3a) is int
  decltype(i)   x3d = i;     // decltype(x3d) is int
  auto          x4a = (i);   // decltype(x4a) is int
  decltype((i)) x4d = (i);   // decltype(x4d) is int&
  auto          x5a = f();   // decltype(x5a) is int
  decltype(f()) x5d = f();   // decltype(x5d) is int&&


  // C++98 init of int
  int x1 = 27; 
  int x2(27);
  
  // C++11 "Uniform Initialization"
  int x3 = { 27 }; 
  int x4 { 27 };
  
  // result is the same for int for all 4 above

  // now auto
  
  auto x1 = 27; 
  auto x2(27); 

  // the above two : type is int, value is 27

  auto x3 = { 27 }; 
  auto x4 { 27 };

  // The above 2 are different though: type is std::initializer_list<int>,  value is { 27 }

  // When the initializer for an auto-declared variable is enclosed in braces,
  // the deduced type is a std::initial izer_list



}
