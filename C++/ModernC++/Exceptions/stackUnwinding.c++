#include <iostream> 

using namespace std; 

/*

Stack unwinding 

In the C++ exception mechanism, control moves from the throw statement to the
first catch statement that can handle the thrown type. When the catch statement
is reached, all of the automatic variables that are in scope between the throw
and catch statements are destroyed in a process that is known as stack
unwinding.

bash-3.2$ ./a.out

 f3() Start
 f2() Start
 f1() Start
 Caught Exception: 100
 f3() End
bash-3.2$

In the above program, when f1() throws exception, its entry is removed from the
function call stack (because it f1() doesn’t contain exception handler for the
thrown exception), then next entry in call stack is looked for exception
handler. The next entry is f2(). Since f2() also doesn’t have handler, its entry
is also removed from function call stack. The next entry in function call stack
is f3(). Since f3() contains exception handler, the catch block inside f3() is
executed, and finally the code after catch block is executed. Note that the
last lines inside f1() and f2() are not executed at all.

On a side note, if there were some local class objects inside f1() and f2(),
destructors for those local objects would have been called in Stack Unwinding
process.

*/

// A sample function f1() that throws an int exception  
void f1() throw (int) { 
  cout<<"\n f1() Start "; 
  throw 100; 
  cout<<"\n f1() End ";  
} 

// Another sample function f2() that calls f1() 
void f2() throw (int) { 
  cout<<"\n f2() Start "; 
  f1(); 
  cout<<"\n f2() End "; 
} 

// Another sample function f3() that calls f2() and handles exception thrown by f1() 
void f3() { 
  cout<<"\n f3() Start "; 
  try { 
    f2(); 
  } 
  catch(int i) { 
    cout<<"\n Caught Exception: "<<i; 
  } 
  cout<<"\n f3() End"; 
} 

// A driver function to demonstrate Stack Unwinding  process 
int main() { 
  f3(); 
  
  getchar(); 
  return 0; 
} 

 
