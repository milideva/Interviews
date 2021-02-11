#include "circle.h"
#include <iostream>

circle::circle(int radius, int color): m_Radius{radius}, shape{color} {
  LOG ;
}

float circle::getArea() const {
  return 3.141f * m_Radius * m_Radius ;
}

void circle::draw() {
  std::cout << "[circle] Drawing with color:" << m_Color << "\n" ;
}
void circle::scale (float scale) {
  LOG;
}

circle::~circle() {
  LOG ;	
}
