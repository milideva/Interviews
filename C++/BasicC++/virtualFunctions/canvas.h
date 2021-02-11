#pragma once
#include "shape.h"

class canvas {
  shape **m_pShape{} ;
  int m_Size{} ;
 public:
  canvas() ;
  void addShape (shape *p) ;
  void renderCanvas() ;
  ~canvas() ;
};

