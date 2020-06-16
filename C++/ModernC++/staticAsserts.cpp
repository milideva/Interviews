#include <cstdio>
#include <vector>
#include <iostream>
#include <type_traits>

using namespace std;

// Example 1
template <typename T, size_t Size>
class Values {
    static_assert(Size > 1, "Use a scalar");
    T values[Size];
};


// Example 2
template <typename T, typename U, typename S>
auto add (T t, U u, S s) {
    static_assert(std::is_integral<T>::value, "T must be an int");
    return t+u+s;
}

int main () {

    // Example 1
    Values<int, 3> val;
    
    // Values<int, 1> noCompile;
    

    // Example 2
    // cout << add("a", "b") << endl;
    cout << add(1, 2, 3) << endl;

    return 0;
}
