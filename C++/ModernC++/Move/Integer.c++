#include "Integer.h"
#include <iostream>

//Default constructor
Integer::Integer () {
  std::cout << "Integer()" << std::endl;
  m_pInt = new int(0);
}

//Parameterized constructor
Integer::Integer (int value) {
  std::cout << "Integer(int)" << std::endl;
  m_pInt = new int(value);
}

//Copy constructor
Integer::Integer (const Integer & obj) {
  std::cout << "Integer(const Integer&)" << std::endl;
  // We've to allocate new resources
  m_pInt = new int(*obj.m_pInt);
}

/* Notes
   To create a move constructor for a C++ class:

   1. Define an empty constructor method that takes an rvalue reference to the
   class type as its parameter,

   2. In the move constructor, assign the class data members from the source
   object to the object that is being constructed,

   3. Assign the data members of the source object to default values. This
   prevents the destructor from freeing resources (such as memory) multiple
   times.

*/

//Move constructor
Integer::Integer (Integer && obj) {
  std::cout << "move constructor Integer(int&&)" << std::endl;
  // shallow copy from obj and set obj's m_pInt to nullptr
  // No new resource allocattion
  m_pInt = obj.m_pInt;

  obj.m_pInt = nullptr;
}

Integer& Integer::operator = (const Integer& rhs) {
  m_pInt = rhs.m_pInt; 
  return *this;
}

/* Notes
   To create a move assignment operator for a C++ class:

   1. Define an empty assignment operator that takes an rvalue reference to the
   class type as its parameter and returns a reference to the class type,

   2. In the move assignment operator, add a conditional statement that performs
   no operation if you try to assign the object to itself,

   3. In the conditional statement, free any resources (such as memory) from the
   object that is being assigned to.

   4. transfer the data members from the source object to the object that is being constructed.

   5. Return a reference to the current object.

*/

// Move assignment operator

Integer& Integer::operator = (Integer&& rhs) {

  std::cout << "move assignment Integer()" << std::endl;

  if (this != &rhs) {
    // free existing resource
    delete m_pInt;

    // copy the pointer from source object
    m_pInt = rhs.m_pInt;

    // Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times.
    rhs.m_pInt = nullptr;
  }

  return *this;
}

int Integer::GetValue () const {
  return *m_pInt;
}

void Integer::SetValue (int value) {
  if (!m_pInt) {
    m_pInt = new int{};
    }
  *m_pInt = value;
}

Integer::~Integer () {
  std::cout << "~Integer()" << std::endl;
  delete m_pInt;
}






