#include <iostream>

using namespace std;

class Car {
  float fuel;
  float speed;
  int passengers;
  static int total;
public:
  Car() = default; // compiler creates default constructor
  ~Car() = default;
  Car(float fuel); // parameterized constructor

  Car (float fuel, int passengers);
  //compiler generates warning if float is passed as int for passengers for above API, so explicitly disable it.
  Car (float fuel, float passengers) = delete; 

  //Car (const Car &c) = default; // compiler creates default copy constructor  anyway without this

  // Unlike default, delete can be used in any function
  // To disable copying of an object - disable copy constructor like Car c1(c2); also disable operator =
  Car (const Car &c) = delete; 
};

int Car::total = 0;

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
