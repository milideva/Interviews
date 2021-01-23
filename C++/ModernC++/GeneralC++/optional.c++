
#include <iostream>
#include <optional>

using namespace std;

// C++17 feature : nullable type

// Old way of doing things 
const char * GetErrorString (int errorNo) {
  switch (errorNo) {
  case 0:
    return "Invalid input" ;
  case 1:
    return "Connection not established yet\n" ;
  default:
    return "" ;
  }
}

optional <const char *> GetErrorStringOp (int errorNo) {
  switch (errorNo) {
  case 0:
    return "Invalid input" ;
  case 1:
    return "Connection not established yet\n" ;
  default:
    return nullopt ;
  }
}

class ContactName {
  string first ;
  optional<string> middle ;
  string last ;
  
public:
  
  ContactName(const string& f, const optional<string>& m, const string& l)
    : first{f},
      middle{m},
      last{l} {
  }
  
  void Print() {
    cout << first << ' ' ;
    cout << middle.value_or("")<< ' ' ;
    cout << last << ' ' ;
    cout << '\n' ;
  }
};

int main() {

  ContactName n1{"Jack", "MiddleName", "Ma"} ;
  ContactName n2{"Dave", "", "Rivers"} ;
  
  n1.Print() ;
  n2.Print() ;
  
  //return 0 ;
  
  optional<int> value{5} ;
  if (value.has_value()) {
    cout << value.value() << endl ;
  }
  if (value) {
    cout << *value << endl; 
  }
  
  value = 1; // can modify
  value.reset() ; // clear it

  //auto message = GetErrorString(1) ;
  //if (strlen(message) != 0) {
  //	cout << message << endl; 
  //} else {
  //	cout << "Unknown error number\n" ;
  //}
  
  try {
    auto errorMessage = GetErrorStringOp(4) ;
    
    //Return contained value or the argument passed in value_or
    cout << errorMessage.value_or("Default") << endl ;
    
    if (errorMessage.has_value()) {
      //Throws exception bad_optional_access if no value in optional
      cout << errorMessage.value() << endl ;
    } else {
      cout << "Unknown error number\n" ;
    }
    
    errorMessage = GetErrorStringOp(4) ;
    
    if (errorMessage) {
      //Undefined behavior when no value exists in optional
      cout << *errorMessage << endl ;
    } else {
      cout << "Unknown error number\n" ;
    }
  } catch (exception &ex) {
    cout << "Exception:"<< ex.what() << endl ;
  }
  return 0;
}
