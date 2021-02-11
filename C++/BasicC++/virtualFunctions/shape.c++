#include "shape.h"

#include <cstdlib>

shape::shape() {
  LOG ;
}

shape::shape(int color): m_Color{color} {
  LOG ;
}

float shape::getArea() const {
  LOG;
  return 0.f ;
}

void shape::draw() {
  LOG;
}

void shape::erase() {
  LOG;
}

void shape::scale (float scale) {
  LOG;
}

shape::~shape() {
  LOG ;
}
