#include <memory>
#include <iostream>
#include <string>

using namespace std;

class Employee; // forward declaration

class Project {

public :
  shared_ptr <Employee> employee;

  Project () {
    cout << "Project() " << endl;
  }

  ~Project () {
    cout << "~Project() " << endl;
  }
};

class Employee {
  
public: 
  
  //shared_ptr<Project> project;
  weak_ptr <Project> project; // this is the solution to circular reference

  Employee() {
    cout << "Employee() " << endl;
  }
  
  ~Employee() {
    cout << "~Employee() " << endl;
  }
};

int main () {
  shared_ptr <Employee> emp { new Employee{} };
  shared_ptr <Project> proj { new Project{} };
  
  emp->project = proj;
  proj->employee = emp;

  // Circular references cause no desrtructor getting called causing memory leak.
  // Solution is to mark either employee or project as a weak pointer.
  // Now both destructors get called

  return 0;
}
