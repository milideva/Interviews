
// User Defined Literals (UDL) are added in C++ from C++11

long double Weight = 2.3; //  pounds? kilograms? grams?

// With UDL, we attach units to the values which has
// following advantages
// 1) The code becomes readable.
// 2) Conversion computations are done at compile time. 
// weight = 2.3kg;
// ratio = 2.3kg/1.2lb;

#include<iostream> 
#include<iomanip> 
using namespace std; 
  
// user defined literals 
  
// KiloGram 
long double operator"" _kg( long double x )  { 
  return x*1000; 
} 
  
// Gram 
long double operator"" _g( long double x ) { 
  return x; 
} 
  
// MiliGram 
long double operator"" _mg( long double x ) { 
  return x / 1000; 
}
  
typedef long double distance_t;

const distance_t km_per_mile = 1.609344L;

distance_t operator"" _km(distance_t val) {
    return val;
}

distance_t operator"" _mi(distance_t val) {
    return val * km_per_mile;
}

int main()  { 
  long double weight = 3.6_kg; 
  cout << weight << endl; 
  cout << setprecision(8) << ( weight + 2.3_mg ) << endl; 
  cout << ( 32.3_kg / 2.0_g ) << endl; 
  cout << ( 32.3_mg *2.0_g ) << endl; 

  // Must have a decimal point to bind to the operator we defined!
  distance_t d1_km { 401.0_km };
  std::cout << "Kilometers in d: " << d1_km << std::endl; // 402

  distance_t d2{ 402.0_mi }; // construct using miles
  std::cout << "Kilometers in d2: " << d2 << std::endl;  //646.956

  // add distances constructed with different units
  distance_t d3 = 36.0_mi + 42.0_km;
  std::cout << "d3 value = " << d3 << std::endl; // 99.9364

  // Distance d4(90.0); // error constructor not accessible

  return 0; 
} 
