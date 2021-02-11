#include <iostream>

#include "circle.h"
#include "rectangle.h"
#include "canvas.h"

int main() {
  circle c{5, 1} ;
  
  std::cout << c.getArea() << '\n' ;
  c.draw() ;

  shape *sp = new circle(5, 1);

  canvas can {};
  can.addShape( new circle {4, 1} );
  can.addShape( new rectangle {10, 4, 1} );

  return 0;  
}
