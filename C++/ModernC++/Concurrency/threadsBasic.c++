#include <iostream>
#include <list>
#include <thread>
#include <string>
#include <mutex>

std::list<int> g_Data;
const int SIZE = 5000000;

std::mutex g_Mutex;

class String {
public:
  String() {
    std::cout << "String()" << std::endl;
  }
  String(const String &) {
    std::cout << "String(const String&)" << std::endl;
  }
  String & operator=(const String&) {
    std::cout << "operator=(const String&)" << std::endl;
    
    return *this;
  }
  ~String() {
    std::cout << "~String()" << std::endl;
  }
};

void Download (const String &file) {
  std::cout << "Threadid:" << std::this_thread::get_id() << std::endl;
  for (int i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << i << ' ';
  }

  for (int i = 0; i < SIZE; ++i) {
    //Use std::lock_guard to lock a mutex (RAII)
    std::lock_guard<std::mutex> mtx(g_Mutex);
    g_Data.push_back(i);
    if (i == 500)
      return;
  }
  std::cout << "Finished" << std::endl; 
}

void Download2 (const String &file) {
  for (int i = 0; i < SIZE; ++i) {
    std::lock_guard<std::mutex> mtx(g_Mutex);
    g_Data.push_back(i);
  }
}

int main() {
  String file;
  std::cout << "main started an operation" << std::endl; 
  
  //use std::ref and std::cref to pass arguments as reference & const reference, respectively
  std::thread t1(Download, std::cref(file) );
  std::thread t2(Download2, std::cref(file) );

  //t1.detach();

  
  //Returns the native type of the thread
  //On Linux, the native type is pthread_t
  //HANDLE handle = t1.native_handle();
  //SetThreadDescription(handle, L"MyThread");
  //pthread_setname_np() for Linux
  
  auto id = t1.get_id();
  std::cout << "t1.get_id():" << id << std::endl; 
  
  int cores = std::thread::hardware_concurrency();
  std::cout << "Cores:" << cores << std::endl;
  
  std::cout << "In [main] join()" << std::endl;
 
  if (t1.joinable()) {
    t1.join() ;
  }
  t2.join();
  
  //system("Pause");
  return 0;
}
