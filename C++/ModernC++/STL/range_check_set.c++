
#include <set>
#include <climits> 
#include <iostream>

using namespace std;

set <pair <int, int>> range_create () {

    set <pair <int, int>> s;
    s.insert( {4, 9});
    s.insert( {40, 90});
    s.insert( {100, 200});
    s.insert( {400, 900});

    return s;
}

bool range_check (int num) {
    set <pair <int, int>> s = range_create();

    auto it = s.lower_bound( {num, INT_MAX} );
    if (it == s.end() || it == s.begin()) 
        return false;
    it--;

    if (it->first <= num && num <= it->second)  
        return true;
    return false;
}

int main () {
    int num = 55;

    string str = range_check(num) ? "Found " : "Not found ";

    cout << str  << num << endl;
    return 0;
}