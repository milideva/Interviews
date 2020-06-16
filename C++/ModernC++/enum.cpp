// g++ enum.cpp -std=c++11

enum OldColor { Red, Blue };
OldColor oc = Red; // Issue1 : pollutes the namespace
int i = oc; // Issue2 : no type safety

enum class NewColor { Red, Blue, Magenta };
NewColor nc = NewColor::Magenta;

int j = nc; // does not compile 

int main () {

    return 0;
}
