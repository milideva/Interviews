#include <iostream> 
using namespace std; 
  
struct demo  { 
    int a; 
}; 

// C++98 different ways to initialize
// scalar with = or ()
// arrays with {}
// C++11 introduced Uniform Initialization - same way for all - using {}
  
void uniform_initialization (void) {
    // C++98 way
    int a1; //uninitialized
    int a2 = 0; // copy initialization
    int a3(5); // direct initialization
    
    string s1; // constructor initializes
    string s2("c++");

    char c1[4]; //uninitialized
    char c2[4] = {'\0'};
    char c3[4] = { 'a', 'b', 'c', 'd'};

    // above initialization are exampls of copy initialization using =

    // Now C++11 Uniform initialization :
    int b1{}; // value initialization
    int b2{5}; // direct initialization
    
    char d1[8]{}; // value initialization 
    char d2[9]{"Howdy"}; // direct initialization

    // also works on heap based allocs
    int *p1 = new int {};
    char *p2 = new char[8] {};
    char *p3 = new char[15] {"whats up?"};

    // auto meaning changed in C++11, it was already present in C and C++98
    // auto derives type from initializer

    auto u =10;
    
}

/ *
    malloc versus new 
    malloc : function
    new : an operator
    
    malloc : requires size
    new : size derived from type
    
    malloc : can not init mem
    new: can init memory

    malloc: can not call constructors
    new : can call constructors
    
    malloc : returns void *, in C++ this needs to be correctly type casted
    new : returns correct type pointer

    malloc : can not be customized
    new : can be customized via overloading

    malloc : return NULL on failure
    new : throws exception 

*/


// C++11 feature : range based loops
void range_based_for_loop (void) {

    int arr[] = { 1, 3, 6, -4, 5 , 7};

    // No index variable i, which is error prone, but less control over iteration
    for (auto a : arr) { // a copy is created in a
        cout << "a:" << a << endl; 
        a = 5; // only copy is modified not the array
    }
    int i = 0;
    for (auto &r : arr) { // NO copy is created in a, just a reference
        cout << "r:" << r << endl;
        r = 55; // modifies the array
        cout << "a[i]:" << arr[i] << endl;
        i++;
    }
    
    i = 0;
    for (const auto &r : arr) { // const ref, now r can not modify array
        cout << "r:" << r << endl;
        // r = 0; // can not modify, compiler wont allow
        cout << "a[i]:" << arr[i] << endl;
        i++;
    }

}

void test2 (void) {
    int foo (10);

    cout << "foo:" << foo << '\n';

    auto bar = ref(foo);

    ++bar;

    cout << "foo:" << foo << '\n';

    auto cbar = cref(foo);
    // ++cbar; // compiler error 

}

void test1 (void) {
    int x = 5; 
    int y = 66; 
    demo d; 
      
    int *p; 
    p = &x; 
    p = &y;                     // 1. Pointer reintialization allowed 
    int &r = x; 

    cout << "x: "<< x << "\t y:" << y << endl; 

    cout << "&r: "<< &r << "r: "<< r << endl;        // 6. Print the value of x     

    // &r = y;                  // 1. Compile Error 
    r = y;                      // 1. x value becomes 6 
    
    cout << "&r: "<< &r << "r: "<< r << endl;        // 6. Print the value of x     
  
    cout << "x: "<< x << "\t y:" << y << endl; 

    p = NULL;            
    // &r = NULL;               // 2. Compile Error 
      
    p++;                        // 3. Points to next memory location 
    r++;                        // 3. x values becomes 7 
      
    cout << "&p: "<< &p << "\t &x: "<< &x << "\t Different address " << endl;    // 4. Different address 
    cout << "&r: "<< &r << "\t &x: " << &x << "\t Same address " << endl;    // 4. Same address 
      
    demo *q = &d; 
    demo &qq = d; 
      
    q->a = 8; 
    // q.a = 8;                 // 5. Compile Error  
    qq.a = 8; 
    // qq->a = 8;               // 5. Compile Error    
  
    cout << "p: "<< p << endl;        // 6. Prints the address 
    cout << "r: "<< r << endl;        // 6. Print the value of x     
}

int main() 
{ 
 
    //test1();
    //test2();
    range_based_for_loop();

    return 0; 
} 

/*

Difference in Reference variable and pointer variable
References are generally implemented using pointers. A reference is same object, just with a different name and reference must refer to an object. Since references can’t be NULL, they are safer to use.

A pointer can be re-assigned while reference cannot, and must be assigned at initialization only.
Pointer can be assigned NULL directly, whereas reference cannot.
Pointers can iterate over an array, we can use ++ to go to the next item that a pointer is pointing to.
A pointer is a variable that holds a memory address. A reference has the same memory address as the item it references.
A pointer to a class/struct uses ‘->'(arrow operator) to access it’s members whereas a reference uses a ‘.'(dot operator)
A pointer needs to be dereferenced with * to access the memory location it points to, whereas a reference can be used directly.

*/
