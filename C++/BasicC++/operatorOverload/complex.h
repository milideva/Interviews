#pragma once

#include <iostream>

#define DOLOG

#ifdef DOLOG
#define LOG std::cout << __PRETTY_FUNCTION__ << " i:" << m_real << " j:" << m_imaginary << "\n" 
#else
#define LOG
#endif

class Complex {
  int m_real {};
  int m_imaginary {};
  public :
  Complex() {
    LOG;
  }

  ~Complex() {
    LOG;
  }

  Complex (int r, int i): m_real { r }, m_imaginary { i } {
    LOG;
  }
  
  void setReal (int r) {
    m_real = r;
  }
  
  void setImaginary (int i) {
    m_imaginary = i;
  }

  int getReal () {
    return m_real;
  }

  int getImaginary () {
    return m_imaginary;
  }
    
  
  Complex operator+ (Complex arg2) {
    
    LOG;
    
    int r = m_real + arg2.m_real;
    int i = m_imaginary + arg2.m_imaginary;
    
    return Complex{r, i};
  }

  void display () {
    std::cout << "Read:" << getReal() << " imaginary:" << getImaginary() << std::endl;
  }
};
