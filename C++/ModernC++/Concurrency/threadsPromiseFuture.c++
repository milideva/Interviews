#include <future>
#include <iostream>
#include <thread>

int Operation (std::promise <int> & data) {
  using namespace std::chrono_literals;
  auto f = data.get_future() ;
  try {
    std::cout << "[Task] Waiting for count\n";
    auto count = f.get(); // gets blocked here until promise has data input
    
    std::cout << "[Task] Count acquired.\n";
    int sum{};
    for (int i = 0; i < count; ++i) {
      sum += i;
      std::cout << '.';
      std::this_thread::sleep_for(300ms);//std::chrono::seconds(1) 
    }
    return sum;
  } catch(std::exception &ex) {
    std::cout << "[Task] Exception:" << ex.what() << std::endl; 
  }
  return 0;
}

int main() {
  using namespace std::chrono_literals ;
  // Promise is an object which can store a value or exception (called shared state)
  // One end, a thread stores in a promise and the other end, another thread gets it from future
  // these operaations are thread safe
  // NOTE promise can only be used once
  
  std::promise<int> data ;
  std::future<int> result = std::async(std::launch::async, Operation, std::ref(data));
  std::this_thread::sleep_for(1s) ;
  std::cout << "[main] Setting the data in promise\n";
  try {
    //throw std::runtime_error{"Data not available"}; // to propagate exception from one thread to another
    data.set_value(10);
    if (result.valid()) {
      auto sum = result.get();
      std::cout << sum << std::endl;
    }
  } catch(std::exception &ex) {
    data.set_exception(std::make_exception_ptr(ex)); // create exception pointer
  }
  return 0;
}
