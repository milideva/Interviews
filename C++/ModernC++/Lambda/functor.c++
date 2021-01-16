#include <iostream>

/*
  Function pointers allow us to pass functions as arguments.
  Disadv. a call is made and can not be inlined or optimised as this is a runtime code.
*/


// using Comparator = bool(*)(int, int);

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

// Function objects provide two main advantages over a straight function call.
// The first is that a function object can contain state. The second is that a
// function object is a type and therefore can be used as a template parameter.

/*
  
  Function Pointer
  - invoked via pointer
  - dynamic
  - specified at run time
  - cannot be optimized / inlined
  - cannot store state
  - Function pointers have fixed parameter types and quantities. 

  Function Object
  - invoked through an object
  - compile time
  - must be specified at compile time
  - can optimize/inline
  - can store state
   (either statically across all instances of the function objects or individually on a particular instance)
  - function object is a type and therefore can be used as a template parameter

  C++11 better way to express Function Objects as Lambda

*/
// Function object is a function of a class or struct that has function call operator () overloaded .
// Function Object as comparator
struct Comp2 {
  bool operator()(int x, int y) {
    return x > y;
  }
};


class Functor {
public:
  int operator() (int a, int b) {
    return a < b;
  }
};

void testFunctorClass (void) {
  Functor f;
  int a = 5;
  int b = 7;
  int ans = f(a, b);
}

int main() {
  Comp2 Comp; // This is now an object and not a function pointer.
  //Comp(3, 5); // internally Comp.operator()(3,5) ;
  
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

  testFunctorClass();

  return 0;
}



/*

* Function Objects and Containers

template <class Key,
    class Traits=less<Key>,
    class Allocator=allocator<Key>>
class set


The second template argument is the function object less. This function object
returns true if the first parameter is less than the second parameter. Since
some containers sort their elements, the container needs a way of comparing two
elements. The comparison is done by using the function object. You can define
your own sorting criteria for containers by creating a function object and
specifying it in the template list for the container.


* Function Objects and Algorithms

template <class ForwardIterator, class Predicate>
ForwardIterator remove_if(
    ForwardIterator first,
    ForwardIterator last,
    Predicate pred);

The last argument to remove_if is a function object that returns a boolean value
(a predicate). If the result of the function object is true, then the element is
removed from the container being accessed by the iterators first and last. You
can use any of the function objects declared in the <functional> header for the
argument pred or you can create your own.

*/
