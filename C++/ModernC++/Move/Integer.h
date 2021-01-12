#pragma once
#include <iostream>

class Integer {
  int *m_pInt;
 public:
  //Default constructor
  Integer ();

  //Parameterized constructor
  Integer (int value);


  // Copy ellision avoid temp objects 
  // So copy constructor or move is not used 
  // To turn off copy ellision, use flag no-elide-constructors
  // g++ -std=c++11 Integer.c++ main.c++ -fno-elide-constructors

  // Copy constructor
  // A copy constructor is used to initialize a previously uninitialized object from some other object's data.
  // If a new object has to be created before the copying can occur, the copy constructor is used.

  Integer (const Integer &obj);

  // An assignment operator is used to replace the data of a previously initialized object with some other object's data.
  // If a new object does not have to be created before the copying can occur, the assignment operator is used.
  Integer& operator = (const Integer& rhs);

  //Move constructor
  // For operations that generate temp objects, use move, especially if it involves pointers
  // Implementation of a copy constructor or assignment or destructor will block implicit generation of move operations

  Integer (Integer &&obj);

  Integer& operator = (Integer&& rhs);

  int GetValue () const;
  void SetValue (int value);
  ~Integer();
};
