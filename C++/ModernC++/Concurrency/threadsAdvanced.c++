#include <future>
#include <iostream>
#include <thread>

int Operation (int count) {
  using namespace std::chrono_literals;
  int sum{};
  for (int i = 0; i < count; ++i) {
    sum += i;
    std::cout << '.';
    std::this_thread::sleep_for(300ms); //literals like ms, need C++14
  }
  return sum; // return holds shared state
}

int main() {
  using namespace std::chrono_literals;
  
  // High level concurrency - dont deal with threads of a particular library (windows/pthreads etc) 
  // Functions that execute in separate thread are called tasks
  // aka Task based concurrency


  /*

    One of the advantages of using std::async instead of manually creating
    std::thread objects is supposed to be that std::async can use thread pools
    under the covers to avoid oversubscription problems.

    There is no guarantee that the task will be executed in a separate thread if
    the launch policy is not specified. Implementation may choose to execute the
    task in same thread depending on certain conditions (too many threads for
    example).

   */
  
  // arg is any callable such as function pointer or function object or a lambda
  // async returns an object of type future and return type (here an int) !
  
  // future<retturn_type> async (callable, args) or
  // future<retturn_type> async (launch_policy, callable, args)
  std::future <int> result = std::async(std::launch::async, Operation, 10);
  
  // launch policies 
  // std::launch::async or std::launch::deferred for synchronous 
  // when deferred policy is used, it runs the task when get is called on the future object
  std::this_thread::sleep_for(1s) ;
  
  /*
    future object has a shared state and can be used for communication between threads
    future is internally created by promise object which is created by async 
    promise as an input channel, future as output channel, used as a pair
    When you return from a task,  set in promise and it's available in future in another thread.
    The thread that reads the shared state will wait until future is ready.
    
    promise/future pair allows safe data sharing without any other synchronization.
    
  */	
  std::cout << "main() thread continues execution...\n";
  
  if (result.valid()) {
    auto timepoint = std::chrono::system_clock::now() ;
    timepoint += 1s ; 
    auto status = result.wait_until(timepoint) ; // allows to poll 
    //auto status = result.wait_for(4s) ;
    switch(status) {
    case std::future_status::deferred:
      std::cout << "Task is synchronous\n" ; // can not wait on it
      break ;
    case std::future_status::ready:
      std::cout << "Result is ready\n" ;
      break ;
    case std::future_status::timeout:
      std::cout << "Task is still running\n" ;
      break ;
    }
    //result.wait() ;
    //Operation(10) ;
    if (result.valid()) {
      auto sum = result.get(); // similar to join
      // after shared state is returned and read using get(), it can not be read again.
      // future object becomes invalid, so must check for valid() first
      
      std::cout << sum << std::endl;
    }
  }
}
