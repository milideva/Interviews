#include "canvas.h"

canvas::canvas() {
  m_pShape = new shape*[10] {};
}

void canvas::addShape (shape* p) {
  m_pShape[m_Size++] = p ;
}

void canvas::renderCanvas () {
  for(unsigned int i = 0 ; i < m_Size;++i) {
    m_pShape[i]->draw() ;
  }
}

canvas::~canvas () {
  for(unsigned int i = 0 ; i < m_Size ;++i) {
    delete m_pShape[i] ;
  }
  delete []m_pShape ;
}
