#include <deque>
#include <iostream>


using namespace std;

void update (deque <int> &dq) {
    auto val = dq.pop_front();
    val *= -10;
    dq.push_front(val);
}

void print (deque <int> &dq) {
    for (auto it = dq.cbegin();  it <= dq.cend(); it++) {
        cout << "dq position: " << *it << endl;
    }
}

int main () {

    deque <int> dq;
    dq.push_front(44);
    dq.push_back(4);
    dq.push_back(33);

    const auto it = find(dq.cbegin(), dq.cend(), 4);
    const auto position = distance(dq.cbegin(), it);

    cout << "dq position: " << position << endl;
    print();
    return 0;
}