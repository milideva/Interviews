#pragma once

#include "shape.h"

class circle : public shape {
  int m_Radius{} ;
 public:
  explicit circle (int radius, int color);
  float getArea() const ;
  void draw() ;
  void scale (float scale);
  ~circle(); 
};

