#include <iostream>

template <typename T, int size, typename Callback>
// ForEach does not know what operation is getting performed for each element
void ForEach (T(&arr)[size], Callback operation) {
  for (int i = 0; i < size - 1; ++i) {
    operation(arr[i]);
  }
}

// How compiler may internally implement 
template<typename T>
struct __Unnamed {
  int offset; 
  __Unnamed(int off) :offset(off) {
    
  }
  void operator()(T &x) /* const */ { // mutable removes this const
    x += offset;
    ++offset;
  }
};

class Product {
  std::string name;
  float price;
public:
  Product(const std::string &n, float p) :name(n), price(p) {
    
  }
  void AssignFinalPrice() {
    float taxes[]{ 12, 5, 5 };
    float basePrice{ price };
    // need to capture 'this' 
    ForEach(taxes, [basePrice, this](float tax) {
      float taxedPrice = basePrice * tax / 100;
      price += taxedPrice;
    });
  }
  float GetPrice()const {
    return price;
  }
};

void lambda_this (void) {
  Product p{ "Watch", 500 };
  p.AssignFinalPrice();
  std::cout << p.GetPrice() << std::endl; 
}

void nested_lambda (void) {
  //Lambda within a lambda
  [](int x) {
    x *= 2;
    [](int x) {
      std::cout << x << std::endl; 
    }(x);
  } (5);
}

#include <fstream>


// Generalized capture (C++ 14)

// In C++14, you can introduce and initialize new variables in the capture
// clause, without the need to have those variables exist in the lambda
// function’s enclosing scope. The initialization can be expressed as any
// arbitrary expression; the type of the new variable is deduced from the type
// produced by the expression. One benefit of this feature is that in C++14 you
// can capture move-only variables (such as std::unique_ptr) from the
// surrounding scope and use them in a lambda.

auto generalized_lambda_capture () {
  int x {5};
  // Generalized capture creates a new variable y
  auto fn = [y = x] (int arg) {
    return y * arg;
  };
  auto ret = fn(35);

  std::ofstream out("test.txt");
  // ofstream can not be copy by val.
  // out leaks outside lambda. hence use move!
  auto write = [out = std::move(out)](auto x) mutable {
    out << x;
  };

  write(200);
}

int main () {

  // atexit C library function takes a callback as input
  // empty capture list, decays lambda into a function pointer
  // Pass in lambda to atexit() as with empty capture list, a type conversion operator of lambda converts lambda into func *
  atexit([]() {
    std::cout << "Program is exiting..." << std::endl; 
  });
  
  int arr[]{ 1,6,8,4,0 };
        	
  ForEach(arr, [](auto x) {
    std::cout << x << " ";
  });
  std::cout << std::endl; 

  int offset = 5;

  // Local variables such as offset are not visible within lambda, need to
  // explicitly capture it in capture list. Global / static are available though (without capture).
  
  ForEach(arr, [offset] (auto &x) {
    x += offset;
  });
  
  int sum {};

  ForEach(arr, [&sum, offset] (auto &x) mutable {

    sum += x;

    x += offset;

    // Modifying captured value inside 
    // 'capture' offset - it's a copy by value and is const by default
    // offset inside lambda is not same as offset outside lambda 
    
    ++offset;

  });
	
  ForEach(arr, [](auto x) {
    std::cout << x << " ";
  });

  std::cout << std::endl; 

  std::cout << "offset: " << offset << std::endl; // offset was pass by value - is still initial value
  std::cout << "sum:" << sum <<  std::endl; // sum was pass by ref


  // & in capture list indicates all var in enclosing scope passed by ref

  sum = 0;
  ForEach(arr, [&, offset](auto &x) { 
    sum += x;
  });
  std::cout << "sum:" << sum <<  std::endl; // sum was pass by ref

  // = in capture list indicates all var in enclosing scope passed by value

  ForEach(arr, [=, &offset] (auto &x) mutable {
    sum += x;
  });

  std::cout << "sum:" << sum <<  std::endl; // sum was pass by val

  
  /* 
     You can capture by both reference and value, which you can specify using & and = respectively:
   
     [&varA] capture by reference
     [&] captures all variables used in the lambda by reference
     [=] captures all variables used in the lambda by value
     [&, varA] captures variables like with [&], but varA by value
     [=, &varA] captures variables like with [=], but varA by reference
     
  */

  lambda_this();
  nested_lambda();
  //generalized_lambda_capture();
  
  return 0;
}
