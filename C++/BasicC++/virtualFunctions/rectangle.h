#pragma once
#include "shape.h"

class rectangle : public shape {
  int m_Height{} ;
  int m_Width{} ;
  
 public:
  rectangle (int color, int height, int width);
  float getArea() const override ;
  void draw() override ;
  void scale(float scale) override ;
};

