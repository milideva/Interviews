#include <tuple>
#include <iostream>
#include <array>

using namespace std;

// C++11 syntax
tuple<double,int> return_two_args_11() {
    return make_tuple(1.0, 2);
}

void test_11 () {
  double a;
  int b;
  tie(a,b) = return_two_args_11();
}

// C++17 syntax
auto return_two_args_17() {
    return tuple(1.0, 2);
}

void test_17() {
  auto [a, b] = return_two_args_17();
}

void test_tuple_reference_17() {
  auto tuple = make_tuple(1, 'a', 2.3);
  
  // unpack the tuple into its individual components

  // Using structured bindings in C++17, you can bind the tuple members
  // directly to named variables without having to use std::get, or declaring
  // the variables first.

  // This technique will also allow you to obtain references to tuple members,
  // something that isn’t possible using std::tie. Here, you’ll get references
  // to the tuple members, and when you change the value of one of them, the
  // value in the tuple changes

  auto& [ i, c, d ] = tuple;

  cout << "i=" << i << ", c=" << c << ", d=" << d << '\n';

  // change the value of i inside the tuple
  i = 2;
  
  // show that the value inside the tuple has changed
  cout << "changed tuple<0>=" << get<0>(tuple) << '\n';
}


struct Foo {
  int i;
  char c;
  double d;
};


// structured bindings can also be used with arrays and structs
void test_struct_array_reference_17 () {
  Foo f { 1, 'a', 2.3 };
  
  // unpack the struct into individual variables declared at the call site
  auto& [ i, c, d ] = f;
  
  cout << "i=" << i << " c=" << c << " d=" << d << '\n';
  
  // change the member c
  c = 'b';

  // show the value changed in f
  cout << "changed f.c=" << f.c << '\n';

  // limitation 1 : all elements must be unpacked
  // limitation 2 : destructuring works only one level deep, no nested destructuring

  array <int32_t, 6> arr{10, 11, 12, 13, 14, 15};
  auto [i1, j, k, l, _dummy1, _dummy2] = arr;

}

#include <map>

map<string, int> get_map() {
  return {
    { "hello", 1 },
    { "world", 2 },
    { "it's",  3 },
    { "me",    4 },
  };
}


/*
  We can also capture as a forwarding reference using auto&&.
  That is, auto&& will resolve to auto& for lvalue references, and auto&& for rvalud references.
*/

void test_forwarding_ref_17() {
  for (auto&& [ k, v ] : get_map())
    cout << "k=" << k << " v=" << v << '\n';
}

int main () {
  
  test_11();
  test_17();
  test_tuple_reference_17();
  test_struct_array_reference_17();
  test_forwarding_ref_17();
  return 0;
}
