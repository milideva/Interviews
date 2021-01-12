#include "car.h"
#include <iostream>

using namespace std;

int Car::total = 0;
Car::Car () : Car (0){

  /*
  ++total;
  fuel = speed = passengers = 0;
  */
  cout << "Car()" << endl;
}

Car::Car (float fuel) : Car (fuel, 0) {
  /*
  this->fuel = fuel;
  ++total;
  speed = passengers = 0;
  */
  cout << "Car(float)" << endl;
}

Car::Car (float fuel, int pass) {

  ++total;

  this->fuel = fuel;
  this->passengers = pass;
  speed = 0;
  cout << "Car(float, float)" << endl;
}

Car::~Car () {
  total--;
  cout << "~Car() : deleted total: " << total << endl;
}

/* 
   Notes :
   Common init code is kept in only one constructor

   default constructor first Car () calls Car (float fuel) before exeecuting its
   body.

   Likewise Car (float fuel) first calls Car (float fuel, int pass) before
   executing its own body

*/
int main () {
  Car tesla;
  Car corolla(10);
  Car maxima(12, 5);
  return 0;
}
