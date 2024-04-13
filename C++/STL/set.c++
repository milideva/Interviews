/*
    Sets (collections of keys)
    - Ordered. Implemented using a BST (RBTree)
    - Use unordered_set for mathematical set (hashtable of keys)
    - No duplicates - use multiset for duplicates
    - Immutable (no update / no modify), because if we allow mutate, it will mess up the order in the BST
    - set/unordered_set/multiset 3 options

    Typical Operations
    insert(newkey) returns a pair 'first' is pos iterator and 'second' is bool
                    if second = true, first = newkey iter
                    if second = false, first = dupkey iter
    iterating: set.begin(), set.end() etc
    find(key) // log(n)
    erase(itr) 
    or 
    erase(key)
    NO MODIFY
*/

#include <set>
#include <cassert>
#include <iostream>

int main () {

    std::set <int> st;

    st.insert(15);
    st.insert(7);
    st.insert(19);
    st.insert(5);

    assert(st.size() == 4);

    std::cout << "set: ";
    for (auto i : st)
        std::cout << i << ' ';
    std::cout << '\n';

    int i = 10;
    auto it = st.find(i);
    if (it == st.end()) {
         std::cout << i << " not found in the set" << '\n';
    }
    i = 15;
    it = st.find(i);
    if (it != st.end()) {
         std::cout << i << " found in the set" << '\n';
    }
    auto itr_bool = st.insert(i);
    if (itr_bool.second == true) {
        std::cout << i << " insert in the set succeeded" << '\n';
    } else {
        std::cout << i << " insert in the set failed" << '\n';
    }
    // erase using iterator
    st.erase(it);
    assert(st.size() == 3);

    st.insert(15);
    assert(st.size() == 4);

    // erase using a key
    st.erase(15);
    assert(st.size() == 3);

    return 0;
}