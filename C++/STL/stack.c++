/*

Stack (LIFO)

push() // pushes in the front
pop() // pops from the front
top() // returns top
empty()
size() // number of elements

Notes:
- No random access
- No iteration, must pop to iterate

*/

#include <cassert>
#include <iostream>
#include <stack>
 
int main() {
    std::stack<int> stk;
 
    stk.push(0); // pushes 0
    stk.push(1); // stk = 1 0
    stk.push(2); // stk = 2 1 0 
    stk.push(3); // stk = 3 2 1 0
 
    assert(stk.top() == 3);
    assert(stk.size() == 4);
 
    stk.pop(); // removes the top element, 3
    assert(stk.size() == 3);
 
    // Print and remove all elements. Note that std::stack does not
    // support begin()/end(), so a range-for-loop cannot be used.
    std::cout << "stack: ";
    for (; !stk.empty(); stk.pop())
        std::cout << stk.top() << ' ';
    std::cout << '\n';
    assert(stk.size() == 0);
}

