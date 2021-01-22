
// 1. template type deduction
// 2. auto 
// 3. decltype

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
