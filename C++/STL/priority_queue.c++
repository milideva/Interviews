/*

Priority queue aka Heap

- A partial order
- Default is max heap
- internally an array, superb cache hit
- For min heap, supply greater<int> 

*/

#include <concepts>
#include <functional>
#include <iostream>
#include <queue>
#include <ranges>
#include <string_view>
#include <vector>
 
 // Ignore the following print code, just look at main() for the usage of minHeap and maxHeap.

template<typename T>
void print(std::string_view name, T const& q) {
    std::cout << name << ": \t";
    for (auto const& n : q)
        std::cout << n << ' ';
    std::cout << '\n';
}
 
template<typename Adaptor>
requires (std::ranges::input_range<typename Adaptor::container_type>)
void print(std::string_view name, const Adaptor& adaptor) {
    struct Printer : Adaptor // to access protected Adaptor::Container c;
    {
        void print(std::string_view name) const { ::print(name, this->c); }
    };
 
    static_cast<Printer const&>(adaptor).print(name);
}
 
int main() {
    const auto data = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
    print("data", data);
 
    std::priority_queue<int> q1; // Max priority queue
    for (int n : data)
        q1.push(n);
 
    print("q1", q1);
 
    // Min priority queue
    // std::greater<int> makes the max priority queue act as a min priority queue
    std::priority_queue<int, std::vector<int>, std::greater<int>>
        minq1(data.begin(), data.end());
 
    print("minq1", minq1);
 
    // Second way to define a min priority queue
    std::priority_queue minq2(data.begin(), data.end(), std::greater<int>());
 
    print("minq2", minq2);
 
    // Using a custom function object to compare elements.
    struct
    {
        bool operator()(const int l, const int r) const { return l > r; }
    } customLess;
    std::priority_queue minq3(data.begin(), data.end(), customLess);
 
    print("minq3", minq3);
 
    // Using lambda to compare elements.
    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q5(cmp);
 
    for (int n : data)
        q5.push(n);
 
    print("q5", q5);
}