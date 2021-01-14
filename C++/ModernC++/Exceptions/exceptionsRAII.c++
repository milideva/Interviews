#include <iostream>
#include <memory>
#include <vector>
#include <random>

class Test {
public:
  Test() { std::cout << "Test():Acquire resources" << std::endl; }
  ~Test() { std::cout << "~Test():Release resources" << std::endl; }
};

// Use either smart pointers or stl containers (vector etc), so that memory is not leaked 
void ProcessRecords(int count) {
  std::unique_ptr<Test> t(new Test); // Smart pointer is local object & thus
                                     // destructor gets called - mem will get
                                     // released on exception.

  if (count < 10)
    throw std::out_of_range("Count should be greater than 10");
  
  std::vector<int> p;
  p.reserve(count);
  
  std::vector<int> records;
  records.reserve(count);
  
  //Process the records
  for (int i = 0; i < count; ++i) {
    records.push_back(i);
  }
  
  std::default_random_engine eng;
  std::bernoulli_distribution dist;
  int errors{};
  
  for (int i = 0; i < count; ++i) {
    try {
      std::cout << "Processing record # : " << i << " ";
      if (!dist(eng)) {
        ++errors;
        throw std::runtime_error("Could not process the record");
      }
      std::cout << std::endl;
    }
    catch (std::runtime_error &ex) {
      std::cout << "[ERROR " << ex.what() << "]" << std::endl;
      if (errors > 4) {
        // Modifying exception object since it was caught by ref
        std::runtime_error err("Too many errors. Abandoning operation");
        ex = err; 
        throw; // rethrowing original exception object, nested exception
      }
    }
  }
}

/*
Old code using raw pointers
*/
void ProcessRecordsOld(int count) {
  /*
    Compare this code with the code that uses RAII.
  */
  Test *t = new Test; // This heap object will be leaked as stack unwinds in exception case.
  if (count < 10)
    throw std::out_of_range("Count should be greater than 10");
  
  int *p = new int[count];
  int *pArray = (int*)malloc(count * sizeof(int));  // Use vector instead, as this will leak in exception case
  if (pArray == nullptr) {
    throw std::runtime_error("Failed to allocate memory");
  }
  //Process the records
  for (int i = 0; i < count; ++i) {
    pArray[i] = i;
  }
  //Unreachable code in case of an exception
  free(pArray);
  delete[] p;
  delete t;
}

int main() {
  try {
    //ProcessRecords(std::numeric_limits<int>::max());
    ProcessRecords(10);
  }
  catch (std::runtime_error &ex) {
    std::cout << ex.what() << std::endl;
  }
  catch (std::out_of_range &ex) {
    std::cout << ex.what() << std::endl;
  }
  catch (std::bad_alloc &ex) {
    std::cout << ex.what() << std::endl;
  }
  
  /*
    std::exception is the base class for all standard
    exception classes. It can be used as a handler if
    the exception handling code is same for all child
    class exception objects
  */
  catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  
  /*
    All-catch handler. Avoid as it does not give any
    information about the exception, so it is difficult
    to take any preventative action
  */
  catch (...) {
    std::cout << "Exception" << std::endl;
  }
  return 0;
}

