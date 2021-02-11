#pragma once

#define DOLOG
#include "logger.h"

class shape {
 protected:
  int m_Color ;
 public:
  shape();
  explicit shape (int color);
  virtual float getArea () const ;
  virtual void draw () ;
  virtual void erase () ;
  virtual void scale (float scale);
  virtual ~shape() ;
};

