
#include <algorithm>
#include <iostream>
#include <limits>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <vector>

template <typename T>
size_t FindArr (const T *pArr, size_t size, const T& element) {
  for (unsigned int i = 0 ; i < size ; ++i) {
    if (pArr[i] == element) {
      return i ;
    }
  }
  return std::numeric_limits<size_t>::max() ;//UINT_MAX
}

template <typename Iterator, typename ElementType>
Iterator Find (Iterator begin, Iterator end, const ElementType & element) {
  while(begin != end) {
    if (*begin == element)
      break ;
    ++begin ;
  }
  return begin ;
}

void Print (std::array<int, 5> arr) {
  for (auto a : arr) {
    std::cout << a << ' ' ;
  }
  
  for (size_t i = 0 ; i < arr.size() /*+ 1*/ ; ++i) {
    std::cout << arr.at(i) << '\n' ;
  }
}


template <typename Container>
void Print (const Container &cont, const char *message="Output", char ch = ' ') {
  std::cout << "#### "<< message << " ####"<<'\n'; 
  /*for (const auto &e : cont) {
    std::cout << e << ' ' ;
    }*/
  auto it = cont.begin();
  while(it != cont.end()) {
    std::cout << *it++ << ch ;
  }
  std::cout << '\n' ;
}

void Array () {
  std::array <int, 5> arr{5,2,1,3,9} ;
  for (size_t i = 0 ; i < arr.size() ; ++i) {
    arr[i] = (i + 1) * 10 ;
  }
  Print(arr) ;
  auto index = FindArr(arr.data(), arr.size(), 30) ;
  std::cout<< "Found at :" << index << '\n' ;
  
  std::cout << "First:" << arr.front() << '\n' ;
  std::cout << "Last:" << arr.back() << '\n' ;
}

void Vector () {
  std::vector <int> data{} ;
  data.reserve(6) ;
  for (size_t i = 0 ; i < 10 ;++i) {
    std::cout << "Size:" << data.size() << " | " ;
    std::cout << "Capacity :" << data.capacity() << '\n' ;
    data.push_back(i) ;
  }
  Print(data, "Vector") ;
  data.resize(20) ;
  /*for (size_t i = 10 ; i < data.size() ; ++i) {
    data[i] = rand() % 50 ;
    }*/
  auto it = data.begin() ;
  it += 10;
  while(it != data.end()) {
    *it++ = rand() % 50 ;
  }
  data.push_back(999) ;
  //data.reserve(100) ;
  /*data.clear() ;
    data.shrink_to_fit() ;*/
  Print(data, "Vector") ;
  std::cout << "Size:" << data.size() << " | " ;
  std::cout << "Capacity :" << data.capacity() << '\n' ;
}

void VectorInsertErase () {
  std::vector<int> data{} ;
  for (size_t i = 0 ; i < 10 ;++i) {
    data.push_back(i) ;
  }
  Print(data, "Vector") ;
  auto beg = data.begin() +2;
  auto end = data.begin() + 7 ;
  //data.erase(beg, end) ;
  for (auto it = data.begin() ;it != data.end(); ) {
    if (*it % 2 == 0) {
      it = data.erase(it );
      continue ;
    }
    ++it ;
  }
  Print(data, "Vector After erase") ;
  
  beg = data.begin() ;
  data.insert(beg,{1,2,3,4}) ;
  Print(data, "Vector After insert") ;
}

void List () {
  std::list<int> data{} ;
  for (size_t i = 0 ; i < 10 ;++i) {
    data.push_back(rand() % 5) ;
  }
  Print(data, "List") ;
  auto beg = data.begin();
  std::advance(beg, 5) ;
  //data.erase(beg) ;
  data.remove(4) ;
  ++beg ;
  --beg ;
  Print(data, "List after remove") ;
}

void ForwardList () {
  std::forward_list<int> data{} ;
  for (size_t i = 0 ; i < 10 ;++i) {
    data.push_front(i) ;
  }
  auto size = std::distance(data.begin(), data.end()) ;
  std::cout << size << '\n' ;
  Print(data, "List") ;
  auto beg = data.begin();
  std::advance(beg, 5) ;
  std::cout << *beg << '\n' ;
  //data.erase(beg) ;
  //data.remove(4) ;
  data.erase_after(beg) ;
  Print(data, "List after remove") ;
}

void Deque () {
  std::deque<int> data{} ;
  for (int i = 0 ; i < 5 ; ++i) {
    data.push_front(i) ;
  }
  for (int i = 0 ; i < 5 ; ++i) {
    data.push_back(i) ;
  }
  Print(data, "deque") ;
}

void Set () {
  std::set<int, std::greater<int>> data{} ;
  for (size_t i = 0 ; i < 10 ;++i) {
    auto info = data.insert(rand() % 5) ;
    if (info.second == false) {
      std::cout << *info.first << '\n' ;
    }else {
      std::cout << "Inserted:" << *info.first << '\n' ;
    }
  }
  Print(data, "set") ;
  auto found = data.find(3) ;
  if (found != data.end()) {
    std::cout << "Found\n" ;
  }
}

void Multiset () {
  std::multiset<int> data{} ;
  for (size_t i = 0 ; i < 10 ;++i) {
    auto info = data.insert(rand() % 5) ;
    std::cout << "Inserted:" << *info << '\n' ;
  }
  Print(data, "set") ;
  auto found = data.equal_range(3) ;
  //std::cout << std::distance(found.first, found.second)<< '\n' ;
  std::cout << data.count(3)<< '\n' ;
  
  while(found.first != found.second) {
    std::cout << *found.first++ << ' ' ;
  }
}

struct Employee {
  std::string m_Name{} ;
  int m_Id{} ;
  Employee(){}
  Employee(const std::string& name, int id)
    : m_Name{name},
      m_Id{id} {
  }
  friend std::ostream& operator<<(std::ostream& os, const Employee& obj) {
    return os
      << obj.m_Name
      << " : " << obj.m_Id;
  }
  friend bool operator<(const Employee & lhs, const Employee & rhs) {
    return lhs.m_Name < rhs.m_Name ;
  }
};

struct EmpGreater {
  bool operator ()(const Employee & lhs, const Employee & rhs)const {
    return lhs.m_Name > rhs.m_Name ;
  }
};

/*
 * Must provide these 
 * 1. Default constructible
 * 2. Destructible
 * 3. Copy/move constructible
 * 4. Relational operators < > != ==
 */

void UserDefVector() {
  std::vector<Employee> v{
    Employee{"Uma", 101},
    {"Sam", 102},
    {"Aryan", 103},
    {"Uma", 104}
  };
  v.resize(10) ;
  v.push_back({"Raidu", 106}) ;
  std::sort(v.begin(), std::end(v), EmpGreater{}) ;
}

void UserDefSet() {
  std::set<Employee, EmpGreater> emps{
    Employee{"Uma", 101},
    {"Sam", 102},
    {"Ayaan", 103},
    {"Uma", 104}
	};
  Print(emps, "Employees", '\n') ;
  auto e = emps.find({"Sam",0}) ;
}

std::ostream & operator<<(std::ostream & out, const std::pair<int, Employee> &pair) {
  return out << pair.first <<":" << pair.second ;
}

void Map() {
  std::map<int, Employee, std::greater<int>> emps{
    std::make_pair(101, Employee{"Uma", 101}),
    std::make_pair(102, Employee{"Sam", 102}),
    std::pair<int, Employee>{103, {"Ayaan", 103}},
    std::pair{104, Employee{"Uma", 104}},
  };
  emps.insert(std::make_pair(105, Employee{"Raidu", 105})) ;
  emps[106] = Employee{"Kiran", 106} ;
  Print(emps, "Employees", '\n') ;
  auto e = emps.find(101) ;
  if (e != emps.end()) {
    std::cout << /*(*e).second */ e->second << '\n' ;
  }
}

int main() {
  try {
    Map();
  }
  catch (const std::exception& ex) {
    std::cout << "Exception:" << ex.what() << '\n';
  }
  return 0;
}
