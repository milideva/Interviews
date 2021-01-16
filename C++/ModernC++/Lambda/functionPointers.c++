#include <iostream>

/*
  Function pointers allow us to pass functions as arguments.
  Disadv. a call is made and can not be inlined or optimised as this is a runtime code.
*/

using Comparator = bool(*)(int, int);

// Sort in ascending or descending order depending on the function pointer 
template <typename T, int size, typename Comparator>
void Sort (T(&arr)[size], Comparator comp) {
  for (int i = 0; i < size-1; ++i) {
    for (int j = 0; j < size - 1; ++j) {
  
      if (comp(arr[j], arr[j + 1])) {
        T temp = std::move(arr[j]);
        arr[j] = std::move(arr[j + 1]);
        arr[j + 1] = std::move(temp);
      }

    }
  }
}

// Function pointers as comparators
// Ascending order
bool Comp (int x, int y) {
  return x > y;
}

// Descending order
bool compDescendingOrder (int x, int y) {
  return x < y;
}

///////////////////////// Function Objects aka functors /////////////////////////

// Function object is a function of a class or struct that has function call operator () overloaded .
//Function Object as comparator
struct Comp2 {
  bool operator()(int x, int y) {
    return x > y;
  }
};

int main() {
  //Comp2 comp;
  Comp(3, 5);//Comp.operator()(3,5) ;
  
  int arr[] { 1,6,8,4,0 };
  std::cout  << "Original order: " ;
  for (auto x : arr) {
    std::cout << x << " ";
  }

  std::cout << std::endl;

  Sort(arr, Comp);
  std::cout  << "Sorted order: " ;
  for (auto x : arr) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  return 0;
}
