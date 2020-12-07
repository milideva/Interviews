#include <iostream> 
using namespace std; 
  
struct demo 
{ 
    int a; 
}; 
  
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
 
    test1();
    test2();

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
