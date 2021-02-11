#include "rectangle.h"

rectangle::rectangle(int color, int height, int width): shape{color},
                                                        m_Height{height},
                                                        m_Width{width} {
}

float rectangle::getArea() const {
  return m_Height * m_Width ;
}

void rectangle::draw() {
  std::cout << "[rectangle] Drawing with color:" << m_Color << '\n'; 
}

void rectangle::scale (float scale) {
  std::cout << "Scaling rectangle\n" ;
}
