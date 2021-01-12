class Car {
  float fuel;
  float speed;
  int passengers;
  static int total;
public:
  Car(); // default constructor 
  ~Car();
  Car(float fuel); // parameterized constructor 
  Car (float fuel, int passengers);
};
