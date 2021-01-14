#include <algorithm> // for lower_bound, upper_bound and sort
#include <iostream>
#include <vector>
 
using namespace std;
 
int main() {
    int gfg[] = { 5, 6, 7, 7, 6, 5, 5, 6 };
 
    vector<int> v(gfg, gfg + 8); // 5 6 7 7 6 5 5 6
 
    sort(v.begin(), v.end()); // 5 5 5 6 6 6 7 7
 
    vector<int>::iterator lower, upper;

    // Note these work on set, map etc as well 
    lower = lower_bound(v.begin(), v.end(), 6); // first itr >= 6
    upper = upper_bound(v.begin(), v.end(), 6); // first itr > 6
 
    cout << "lower_bound for 6 at position "
         << (lower - v.begin() + 1) << '\n';
    cout << "upper_bound for 6 at position "
         << (upper - v.begin() + 1) << '\n';
 
    return 0;
}
