#pragma once
#include <iostream>
#include <memory>

class Integer {
  int *m_pInt;
 public:
  //Default constructor
  Integer () : Integer(0){
  }

  //Parameterized constructor
  Integer (int value) {
    m_pInt = new int{value};
  }

  // g++ -std=c++11 Integer.c++ main.c++
  int GetValue () const {
    return *m_pInt;
  }

  void SetValue (int value) {
    *m_pInt = value;
  }
  // Destructor
  ~Integer() {
    delete m_pInt;
  }
};
