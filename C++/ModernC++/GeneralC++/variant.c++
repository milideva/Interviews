#include <iostream>
#include <variant>
#include <string>

using namespace std;

// This is a C++17 feature
// type safe Union

/*

union S {
    std::string str;
    std::vector<int> vec;
    ~S() { } // what to delete here?
};

int main() {
    S s = {"Hello, world"};
    // at this point, reading from s.vec is undefined behavior
    std::cout << "s.str = " << s.str << '\n';

    // you have to call destructor of the contained objects!
    s.str.~basic_string<char>();

    // and a constructor!
    new (&s.vec) std::vector<int>;

    // now, s.vec is the active member of the union
    s.vec.push_back(10);
    std::cout << s.vec.size() << '\n';

    // another destructor
    s.vec.~vector<int>();
}

*/

struct Number {
  int m_Num {} ;
  Number (int num): m_Num{num} {
    std::cout << __func__ << std::endl;
  }
  
  Number () {
    std::cout << __func__ << std::endl;
  }
  ~Number () {
    std::cout << __func__ << std::endl;
  }
  
  Number (const Number& other) {
    m_Num = other.m_Num ;
    std::cout << __func__ << std::endl;
  }
  
  Number (Number&& other) noexcept {
    m_Num = other.m_Num ;
    other.m_Num = 0 ;
    std::cout << __func__ << std::endl;
  }

  Number& operator = (const Number& other) {
    std::cout << __func__ << std::endl;
    if (this == &other){
      return *this;
    }
    m_Num = other.m_Num ;
    
    return *this;
  }
  
  Number& operator = (Number&& other) noexcept {
    std::cout << __func__ << std::endl;
    if (this == &other)
      return *this;
    m_Num = other.m_Num ;
    other.m_Num = 0 ;
    
    return *this;
  }
  friend std::ostream& operator <<(std::ostream &out, const Number &n) {
    return out << n.m_Num ;
  }
};

struct Visitor {
  void operator()(const std::string &s)const {
    std::cout << "string:" <<  s << std::endl; 
    
  }
  void operator()(int x)const {
    std::cout << "int:" << x << std::endl ;
  }
  void operator()(const Number &n)const {
    std::cout << "Number:" << n << std::endl; 
    
  }
};

struct Modifier {
  void operator()( std::string &s)const {
    s += " modified string" ;
	}
  void operator()(int& x)const {
    x += 1000 ;
  }
  void operator()( Number &n)const {
    n = 999 ;
  }
};

int main() {
  using namespace std::string_literals ;
  try {
    std::variant <string, int> vSI{5};
    auto val = get<int>(vSI);
    val = get<1>(vSI);
    
    auto activeIndex = vSI.index();
    cout << "activeIndex:" << activeIndex << endl;
    
    auto p = std::get_if<std::string>(&vSI); // Does NOT throw exception, returns nullptr
    if (p == nullptr) {
      std::cout << "Not active\n";
    } else {
      std::cout << *p << std::endl;
    }
    
    std::variant <std::string, int, Number> v{ 7 };
    /*	std::visit(Modifier{}, v) ;
        std::visit(Visitor{}, v) ;
	
        v = "C++" ;
        std::visit(Modifier{}, v) ;
        std::visit(Visitor{}, v) ;
        
        v.emplace<Number>(100) ;
        std::visit(Modifier{}, v) ;
        std::visit(Visitor{}, v) ;*/

    v = "using lambda" ; // lambda as a visitor
    
    auto visitorUsingLambda = [](auto &x) {
      using T = std::decay_t < decltype(x) > ; // use decay to transform ref from decltype to basic type
      if constexpr (std::is_same_v<T, int>){
        std::cout << "int : " << x << std::endl; 
      } else if constexpr (std::is_same_v<T, std::string>){
        std::cout << "string:" << x << std::endl; 
      } else if constexpr(std::is_same_v<T, Number>){
        std::cout << "Number:" << x << std::endl ;
      }
    };
    std::visit(visitorUsingLambda,v) ;
    
    v = 555 ;
    std::visit(visitorUsingLambda,v) ;
    
    v = Number{3} ;
    std::visit(visitorUsingLambda,v) ;
    
    // how to assign  get returns a reference 
    v = Number{1} ;
    v.emplace<Number>(100) ;
    //std::get<Number>(v) = 100 ;
    /*auto val = std::get<int>(v);
      val = std::get<1>(v);
      
      auto activeIndex = v.index();
    */ 
  } catch (std::exception& ex) {
    std::cout << "Exception:" << ex.what() << std::endl;
  }
}
