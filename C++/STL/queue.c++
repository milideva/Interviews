/*

Queue (FIFO)

push() // pushes in the back
pop() // pops from the front
front() // returns front
back() // returns back
empty()
size() // number of elements

Notes:
- No random access
- No iteration, must pop to iterate, if you can not pop, then use deque

*/

#include <cassert>
#include <iostream>
#include <queue>
 
int main() {
    std::queue<int> q;
 
    q.push(0); // back pushes 0
    q.push(1); // q = 0 1
    q.push(2); // q = 0 1 2
    q.push(3); // q = 0 1 2 3
 
    assert(q.front() == 0);
    assert(q.back() == 3);
    assert(q.size() == 4);
 
    q.pop(); // removes the front element, 0
    assert(q.size() == 3);
 
    // Print and remove all elements. Note that std::queue does not
    // support begin()/end(), so a range-for-loop cannot be used.
    std::cout << "queue: ";
    for (; !q.empty(); q.pop())
        std::cout << q.front() << ' ';
    std::cout << '\n';
    assert(q.size() == 0);
}

