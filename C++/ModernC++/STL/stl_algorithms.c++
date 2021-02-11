#include <algorithm>
#include <iostream>
#include <vector>

template<typename Iterator, typename Callback>
auto GetMatchedElements(Iterator  begin, Iterator end, Callback callback) {
  std::vector<typename Iterator::value_type> even_nos{} ;
  std::for_each(begin, end, [&even_nos, callback](typename Iterator::value_type x) {
    if(callback(x)) {
      even_nos.push_back(x) ;
    }
  }) ;
  return even_nos ;
}

int main() {
 
  std::vector<int> data {1,5,3,7,1,9,6,0} ;
  for(auto e : data) {
    std::cout << e << ' ' ;
  }
  std::cout << '\n' ;

  int value {3};

  //size_t i = 0 ;
  //for( ; i < data.size() ; ++i) {
  //	if(data[i] == value ) {
  //		break ;
  //	}
  //}
  //if(value != data.size()) {
  //	std::cout << "Found at :" << i <<'\n' ;
  //}
  

  /*
    Returns an iterator to the first element in the range [first, last] for
    which pred(Unary Function) returns true. If no such element is found, the
    function returns last.
  */
  
  //auto found = std::find(data.begin(), data.end(), value) ;
  //if (found != data.end()) {
  //  std::cout << "Found at index:" <<  found - data.begin() << '\n' ;
  //}
  
  auto found = std::find_if(data.begin(), data.end(), [](int x) {
  	return x % 2== 0 ;
  }) ;

  if (found != data.end()) {
  	std::cout << "Found evens:" <<  *found  << '\n' ;
  }
  
  /*auto found = std::count(data.begin(), data.end(), 1) ;
    std::cout << "Count:" <<  found  << '\n' ;*/
  
  //auto found = std::count_if(data.begin(), data.end(), [](int x) {
  //	return x % 2 != 0 ;
  //}) ;
  //std::cout << "Count:" <<  found  << '\n' ;
  
  //auto anyEven = std::any_of(data.begin(), data.end(), [](int x) {
  //	return x % 2 == 0 ;
  //}) ;
  //std::cout << "Any even?" << std::boolalpha << anyEven << '\n' ;
  
  //
  //auto even_nos = GetMatchedElements(data.begin(), data.end(), [](int x) {
  //	 return (x % 2 == 0) ;
  //});
  //for(auto e : even_nos) {
  //	std::cout << e << '\n' ;
  //}
  
  //Erase-remove idiom
  /*auto new_end = std::remove(data.begin(), data.end(),1) ;
    data.erase(new_end, data.end()) ;*/
  
  std::erase(data, 1) ; //C++20
  for(auto e : data) {
    std::cout << e << ' ' ;
  }
  std::cout << "\n";

  return 0;
}
