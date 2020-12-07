// priority_queue:: push/pop/top/size/empty these are the only ops on a PQ
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>

using namespace std;

class Car {
public :
  int speed;
  string type;
  
  Car () {};
  ~Car () {};
  
  Car (int speed, string type) {
    this->speed = speed;
    this->type = type;
  }
  
  bool operator < (const Car & c1) const {
    return this->speed < c1.speed;
  } 
};


class node {
public:
  int x; 
  int y;
  int z;
  
  node ( int xi, int yi, int zi) {
    x = xi; y = yi; z = zi;
  }
};

struct comparator {
  bool operator() (node &n1, node &n2) {
    int sum1 = n1.x + n1.y + n1.z;
    int sum2 = n2.x + n2.y + n2.z;
    return sum1 < sum2;
  }
};

int main () {

  // 1. Simple priority queue - default is max heap
  
  priority_queue<int> mypq;
  
  mypq.push(125);
  mypq.push(30);
  mypq.push(100);
  mypq.push(25);
  mypq.push(125);
  
  mypq.push(140);
  
  // it's not possible to iterate over a priority queue without popping elements
  // solution : make a copy of it like this :
  priority_queue <int> temp_pq = mypq;
  
  
  std::cout << "Popping out elements... default is max heap, it allows duplicates" << endl;
  while (!temp_pq.empty()) {
    std::cout << ' ' << temp_pq.top();
    temp_pq.pop();
  }
  std::cout << '\n';
  
  
  // 2. Creates a min heap, built in compare function greater for minHeap  
  std::priority_queue <int, vector<int>, greater<int> > pq; 
  pq.push(5); 
  pq.push(1); 
  pq.push(10); 
  pq.push(30); 
  pq.push(20); 
  
  std::cout << "Popping out elements...min heap";
  
  // One by one extract items from min heap 
  while (pq.empty() == false) { 
    std::cout << pq.top() << " "; 
    pq.pop(); 
  } 
  std::cout << '\n';

  // 3. With '<' operator overloading 
  
  priority_queue <Car> car_pq;
  car_pq.emplace(50, "truck");
  car_pq.emplace(30, "electric");
  car_pq.emplace(40, "sedan");
  car_pq.emplace(100, "racer");
  
  while (!car_pq.empty()) {
    cout << " Speed " << car_pq.top().speed << endl;
    car_pq.pop();
  }
  
  // 4. Custom data type and custom compare function 
  
  priority_queue <node, vector<node>, comparator> node_pq;
  
  node_pq.emplace(10, 20, 100);
  node_pq.push(node(10, 20, 30));
  node_pq.push(node(10, 20, 3));
  node_pq.emplace(10, 20, 300);
  
  while (!node_pq.empty()) {
    auto [x, y, z] = node_pq.top();
    cout << "x " << x << " y: " << y << " z: " << z << endl;
    node_pq.pop();
  }
  
  return 0;
}
