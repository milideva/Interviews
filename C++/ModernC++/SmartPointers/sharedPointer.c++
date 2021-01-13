#include <memory>
#include <iostream>
#include <string>

using namespace std;

/*
  The shared_ptr type is a smart pointer in the C++ standard library that is
  designed for scenarios in which more than one owner might have to manage the
  lifetime of the object in memory. After you initialize a shared_ptr you can
  copy it, pass it by value in function arguments, and assign it to other
  shared_ptr instances. All the instances point to the same object, and share
  access to one "control block" that increments and decrements the reference
  count whenever a new shared_ptr is added, goes out of scope, or is reset. When
  the reference count reaches zero, the control block deletes the memory
  resource and itself.

*/
class Project {
  string name;
public :
  Project (string str) {
    name = str;
  }
  ~Project () {
    cout << "~Project() " << name << endl;
  }
};

class Employee {
  //Project *project;
  shared_ptr<Project> project;
  string name;
  
public: 
  Employee (string str) {
    name = str;
  }
/*
  void assignProject (Project *pr) {
    project = pr;
  }
*/
  void assignProject (shared_ptr<Project> pr) {
    project = pr;
  }

/*
  Project *getProject (void) {
    return project;
  }
*/
  shared_ptr <Project> getProject (void) {
    return project;
  }

  string getName () {
    return name;
  }

  ~Employee() {
    cout << "~Employee() " << name << endl;
  }
};

void comparison (void) {
  /// Initialize two separate raw pointers which point to the same values.
  auto project1 = new Project("YMCA");
  auto project2 = new Project("YMCA");

  // Create two unrelated shared_ptrs.
  shared_ptr<Project> p1(project1);    
  shared_ptr<Project> p2(project2);
  
  // Unrelated shared_ptrs are never equal.
  cout << "p1 < p2 = " << std::boolalpha << (p1 < p2) << endl;
  cout << "p1 == p2 = " << std::boolalpha <<(p1 == p2) << endl;
  
  // Related shared_ptr instances are always equal.
  shared_ptr<Project> p3(p2);
  cout << "p3 == p2 = " << std::boolalpha << (p3 == p2) << endl;   
}

/*
  Pass the shared_ptr by value. This invokes the copy constructor, increments
  the reference count, and makes the callee an owner. There's a small amount of
  overhead in this operation, which may be significant depending on how many
  shared_ptr objects you're passing. Use this option when the implied or
  explicit code contract between the caller and callee requires that the callee
  be an owner.
*/
void passByValue (shared_ptr<Employee> spVal) {
  cout << __FUNCTION__ << "(): Employee:" << spVal->getName() << " refcount:" << spVal.use_count() << endl;
}

/*
  Pass the shared_ptr by reference or const reference. In this case, the
  reference count isn't incremented, and the callee can access the pointer as long
  as the caller doesn't go out of scope. Or, the callee can decide to create a
  shared_ptr based on the reference, and become a shared owner. Use this option
  when the caller has no knowledge of the callee, or when you must pass a
  shared_ptr and want to avoid the copy operation for performance reasons. 

*/

void passByRef (shared_ptr<Employee>& spRef) {
  cout << __FUNCTION__ << "(): Employee:" << spRef->getName() << " refcount:" << spRef.use_count() << endl;
}


/*
  Pass the underlying pointer or a reference to the underlying object. This
  enables the callee to use the object, but doesn't enable it to share ownership
  or extend the lifetime. If the callee creates a shared_ptr from the raw
  pointer, the new shared_ptr is independent from the original, and doesn't
  control the underlying resource. Use this option when the contract between the
  caller and callee clearly specifies that the caller retains ownership of the
  shared_ptr lifetime.
*/

void passByRaw (Employee* e) {
  shared_ptr <Employee> spe(e);
  cout << __FUNCTION__ << "(): Employee:" << spe->getName() << " refcount:" << spe.use_count() << endl;
  // This can blow up. Avoid at any cost.
}


/*
  When you're deciding how to pass a shared_ptr, determine whether the callee
  has to share ownership of the underlying resource. An "owner" is an object or
  function that can keep the underlying resource alive for as long as it needs
  it. If the caller has to guarantee that the callee can extend the life of the
  pointer beyond its (the function's) lifetime, use the first option. If you
  don't care whether the callee extends the lifetime, then pass by reference and
  let the callee copy it or not.

  If you have to give a helper function access to the underlying pointer, and
  you know that the helper function will just use the pointer and return before
  the calling function returns, then that function doesn't have to share
  ownership of the underlying pointer. It just has to access the pointer within
  the lifetime of the caller's shared_ptr. In this case, it's safe to pass the
  shared_ptr by reference, or pass the raw pointer or a reference to the
  underlying object. Passing this way provides a small performance benefit, and
  may also help you express your programming intent.

  Sometimes, for example in a std::vector<shared_ptr<T>>, you may have to pass
  each shared_ptr to a lambda expression body or named function object. If the
  lambda or function doesn't store the pointer, then pass the shared_ptr by
  reference to avoid invoking the copy constructor for each element.
*/

int main () {
  
  /*
    Whenever possible, use the make_shared function to create a shared_ptr when
    the memory resource is created for the first time. make_shared is
    exception-safe. It uses the same call to allocate the memory for the control
    block and the resource, which reduces the construction overhead. If you
    don't use make_shared, then you have to use an explicit new expression to
    create the object before you pass it to the shared_ptr constructor.
  */

  //Project *p = new Project("Apollo"); // C++98 way


  // Less efficient : creates a "no named" variable for other code to access.
  // shared_ptr<Project> sp { new Project { "Apollo" }};

  shared_ptr <Project> sp = make_shared <Project> ("Apollo");
  Employee  *e1 = new Employee("John");
  Employee e2("Sam");

  e1->assignProject(sp);
  e2.assignProject(sp);

  // When Declaration is separate from initialization, use nullptr to make intent clear
  shared_ptr <Project> sp2 {nullptr};
  sp2 = make_shared<Project> ("Apollo2");
  
  //Initialize with copy constructor. Increments ref count.
  auto sp3(sp2);
  
  //Initialize via assignment. Increments ref count.
  auto sp4 = sp2;

  // swap pointers as well as ref counts.
  sp.swap(sp2);

  shared_ptr <Employee> se1 = make_shared <Employee> ("Dev");
  shared_ptr <Employee> se2(se1);

  cout << "In main Employee:" << se1->getName() << " refcount:" << se1.use_count() << endl;

  passByValue(se1);
  cout << "In main Employee:" << se1->getName() << " refcount:" << se1.use_count() << endl;

  passByRef(se1);
  cout << "In main Employee:" << se1->getName() << " refcount:" << se1.use_count() << endl;

  passByRaw(e1);
  cout << "In main Employee:" << se1->getName() << " refcount:" << se1.use_count() << endl;

  comparison();

  return 0;
}
