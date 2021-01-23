#include <any>
#include <iostream>

using namespace std;

/*
  A C++17 feature

  C++ is strongly typed
  void * disadv :
  - not typesafe 
  - no way to know type
  - need to manage the object lifetime
*/

struct Number {
  int m_Num{} ;
  Number (int num): m_Num{num} {
    cout << __PRETTY_FUNCTION__ << endl;
  }
  
  Number () {
    cout << __PRETTY_FUNCTION__ << endl;
  }
  ~Number () {
    cout << __PRETTY_FUNCTION__ << endl;
  }
  
  Number (const Number& other) {
    m_Num = other.m_Num ;
    
    cout << __PRETTY_FUNCTION__ << endl;
  }
  
  Number (Number&& other) noexcept {
    m_Num = other.m_Num ;
    other.m_Num = 0 ;
    cout << __PRETTY_FUNCTION__ << endl;
  }
  
  Number& operator=(const Number& other) {
    cout << __PRETTY_FUNCTION__ << endl;
    if (this == &other){
      return *this;
    }
    m_Num = other.m_Num ;
    return *this;
  }
  
  Number& operator=(Number&& other) noexcept {
    cout << __PRETTY_FUNCTION__ << endl;
    if (this == &other)
      return *this;
    m_Num = other.m_Num ;
    other.m_Num = 0 ;
     return *this;
  }
  friend ostream& operator <<(ostream &out, const Number &n) {
    return out << n.m_Num ;
  }
};

void Basics() {
  any v1 = 5;
  //v1 = "Hello"s ;
  v1.reset() ;
  if (v1.has_value()) {
    if (v1.type() == typeid(int)) {
      cout << any_cast<int>(v1) << endl; 
    }
  }
  try {
    cout << any_cast<string>(v1) << endl; 
  } catch (exception &ex) {
    cout << "Exception:" << ex.what() << endl; 
  }
}

int main() {
  using namespace string_literals ;
  //any number{Number{5}} ;
  auto n1 = make_any<Number>(5) ;
  //n1.reset() ;
  n1 = 5 ;
  auto &n2 = any_cast<int&>(n1) ; // use ref to modify, otherwise copy by value
  n2 = 100 ;
  cout << any_cast<int>(n1) << endl ;
  
  auto p = any_cast<int>(&n1) ; // getting a pointer 
  *p = 200 ;
  cout << *any_cast<int*>(p) << endl; 

  return 0;
}
