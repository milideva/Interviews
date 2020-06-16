
#include <iostream>
using namespace std;


// Example 1
auto sum () {
    return 0;
}

template <typename Head, typename ... Tail>
auto sum (Head h, Tail ... t) {
    return h + sum(t...);
}


// Example 2
// returns a pair object (multiple things returned)
auto sum_product (int a, double b) {
	return make_pair(a+b, a*b);
}


int main () {

    cout << sum(2, 4.5, 55) << endl;

    // Older way of doing things.

 	auto values = sum_product(5, 100.1);
 	auto s = get<0>(values);

 	cout << "Old way : sum_product: sum = " << s << endl;

 	// Newer way of doing this 
 	float f;
 	tie(f, ignore) = sum_product(5, 55.55);
 	cout << "New way : sum_product: sum = " << f << endl;

    return 0;
}
