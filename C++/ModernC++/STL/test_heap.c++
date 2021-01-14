#include <iostream>
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector> 
#include <string>

// g++ -std=c++17 test_heap.c++ -g ; lldb a.out
// step through and print v after each step
using namespace std;

void print_array (string s, vector<int>& v) {
  std::cout << s << "vector :";
  for (unsigned i=0; i<v.size(); i++)
    std::cout << ' ' << v[i];

  std::cout << '\n';
  cout << "max heap v.front " << v.front() << '\n';
  cout << "max heap v.back " << v.back() << '\n';
  cout << endl;
}

int main () {
  int myints[] = {10, 1, 27, 20,30,5,15};

  std::vector<int> v(myints, myints + 7);
  print_array("initial ", v);

  cout << "******* NOTE Default is MAX-HEAP ***** " << endl << endl;
  std::make_heap (v.begin(),v.end());
  print_array("after make_heap ", v);

  // pop_heap moved it from the top of heap to last elem of vector
  pop_heap (v.begin(),v.end()); 
  print_array("after pop_heap ", v);

  // remove the last elem of vector - this is the max (or min)
  v.pop_back();
  print_array("after pop_heap() ", v);

  // This is your regular push back on vector, may mess up heap
  v.push_back(99); 
  print_array("after v.push_back of 99 ", v);

  // run heapify on heap by calling push_heap()
  std::push_heap (v.begin(),v.end());
  // now it will be a good heap, check the front()
  print_array("after push_heap ", v);

  // sorting may mess up heap - this is your regular sort on vector
  std::sort_heap (v.begin(), v.end());
  print_array("after sort_heap() final sorted ", v);

  return 0;
}
