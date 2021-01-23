#include <iostream>
#include <variant>
#include <string>

using namespace std;

// This is a C++17 feature
// type safe Union

/* Old way of using Unions - quite painful
union S {
    string str;
    vector<int> vec;
    ~S() { } // what to delete here?
};

int main() {
    S s = {"Hello, world"};
    // at this point, reading from s.vec is undefined behavior
    cout << "s.str = " << s.str << '\n';

    // you have to call destructor of the contained objects!
    s.str.~basic_string<char>();

    // and a constructor!
    new (&s.vec) vector<int>;

    // now, s.vec is the active member of the union
    s.vec.push_back(10);
    cout << s.vec.size() << '\n';

    // another destructor
    s.vec.~vector<int>();
}

*/


/*
  New way of using variant :

  You know what’s the currently used type via index() or check via
  holds_alternative.

  You can access the value by using get_if or get (but that might throw
  bad_variant_access exception)

  Type Safety - the variant doesn’t allow to get a value of the type that’s not
  active

  If you don’t initialize a variant with a value, then the variant is
  initialized with the first type. In that case the first alternative type must
  have a default constructor.
  
  No extra heap allocation happens

  You can use a visitor to invoke some action on a currently hold type.

  The variant class calls destructors and constructors of non-trivial types, so
  in the example, the string object is cleaned up before we switch to new
  variants.

*/


struct Number {
  int m_Num {} ;
  Number (int num): m_Num{num} {
    //cout << __func__ << endl;
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
    cout << __func__ << endl;
  }
  
  Number (Number&& other) noexcept {
    m_Num = other.m_Num ;
    other.m_Num = 0 ;
    cout << __func__ << endl;
  }

  Number& operator = (const Number& other) {
    cout << __func__ << endl;
    if (this == &other){
      return *this;
    }
    m_Num = other.m_Num ;
    
    return *this;
  }
  
  Number& operator = (Number&& other) noexcept {
    cout << __func__ << endl;
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

struct Visitor {
  void operator()(const string &s)const {
    cout << "string:" <<  s << endl; 
    
  }
  void operator()(int x)const {
    cout << "int:" << x << endl ;
  }
  void operator()(const Number &n)const {
    cout << "Number:" << n << endl; 
    
  }
};

struct Modifier {
  void operator()( string &s)const {
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
  using namespace string_literals ;

  try {
    variant <string, int> vSI{5};
    auto val = get<int>(vSI);
    val = get<1>(vSI);
    
    auto activeIndex = vSI.index();
    cout << "activeIndex:" << activeIndex << endl;
    
    auto p = get_if<string>(&vSI); // Does NOT throw exception, returns nullptr
    if (p == nullptr) {
      cout << "Not active\n";
    } else {
      cout << *p << endl;
    }
    
    variant <string, int, Number> v{ 7 };
    /*	visit(Modifier{}, v) ;
        visit(Visitor{}, v) ;
	
        v = "C++" ;
        visit(Modifier{}, v) ;
        visit(Visitor{}, v) ;
        
        v.emplace<Number>(100) ;
        visit(Modifier{}, v) ;
        visit(Visitor{}, v) ;*/

    v = "using lambda" ; // lambda as a visitor
    
    auto visitorUsingLambda = [](auto &x) {
      using T = decay_t < decltype(x) > ; // use decay to transform ref from decltype to basic type
      if constexpr (is_same_v<T, int>) {
        cout << "int : " << x << endl; 
      } else if constexpr (is_same_v<T, string>) {
        cout << "string:" << x << endl;
      } else if constexpr(is_same_v<T, Number>) {
        cout << "Number:" << x << endl;
      }
    };

    visit(visitorUsingLambda, v) ;
    
    v = 555 ;
    visit(visitorUsingLambda, v) ;
    
    v = Number{3} ;
    visit(visitorUsingLambda, v) ;
    
    // how to assign  get returns a reference 
    v = Number{1} ;
    v.emplace<Number>(100) ;
    //get<Number>(v) = 100 ;
    /*auto val = get<int>(v);
      val = get<1>(v);
      
      auto activeIndex = v.index();
    */ 
  } catch (exception& ex) {
    cout << "Exception:" << ex.what() << endl;
  }
}
