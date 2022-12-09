// set::lower_bound/upper_bound
#include <iostream>
#include <set>

using namespace std;

// sets are implemented as a BST (default sorting is < )
// Internally uses *RB-tree* which is a Balanced tree.
// No duplicates allowed - if you need duplicates, use multiset
// Only insert and erase  and find - NO modify 
// Can not update an element - use map instead if u want to update
// No need to sort every time after every insert (which is required for a vector)
// For sort(v.begin(), v.end()) it takes nlog(n). 
// For set, since it's sorted, insert is just log(n).

// multi set allows duplicates
// unordered_set is simply a hash table



/*
  A priority queue only gives you access to one element in sorted order -- i.e., 
  you can get the highest priority item, and when you remove that, 
  you can get the next highest priority, and so on. 
  A priority queue also allows duplicate elements, so it's more like a multiset than a set.

  A set allows you full access in sorted order, so you can, for example, 
  find two elements somewhere in the middle of the set, then traverse in order from 
  one to the other. 

std::priority_queue allows to do the following:
  Insert an element O(log n)
  Get the smallest element O(1)
  Erase the smallest element O(log n)
  
while std::set has more possibilities:
  Insert any element O(log n) and the constant is greater than in std::priority_queue
  Find any element O(log n)
  Find an element, >= than the one your are looking for O(log n) (lower_bound)
  Erase any element O(log n)
  Erase any element by its iterator O(1)
  Move to previous/next element in sorted order O(1)
  Get the smallest element O(1)
  Get the largest element O(1)

*/
set<int>::iterator test_set_find_count (set <int> &myset, int val) {

  // find()
  // returns An iterator to the element, if val is found, or set::end otherwise.
  auto it = myset.find(val);
  if (it != myset.end()) {
    std::cout << "find(): " << *it << " is an element of myset.\n";
  }

  // count()
  // Logarithmic in size.
  // returns 1 if the container contains an element equivalent to val, or zero otherwise.
    if (myset.count(val) != 0)
      std::cout << "count(): " << val << " is an element of myset.\n";
    else
      std::cout << "count(): " << val << " is not an element of myset.\n";
    
    return it;
}
void test_set_insert (set <int> &myset) {

    for (int i = 1; i < 10; i++) 
      myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

    // size
    std::cout << "myset size: " << myset.size() << '\n';

    // insert can fail, it returns a pair
    // pair<set<int>::iterator, bool> iret;
    // iret = myset.insert(20);
    // return a pair, pair::first set to an iterator pointing to 
    // either the newly inserted element or to the element already in the set.
    auto iret = myset.insert(20);
    if (iret.second == false) {  // duplicates not allowed, false if elem NOT inseted
        cout << "Duplicate not allowed " << endl;
        auto it = iret.first; // it now points to 20
        cout << "setting iterator pointing to existing element: " << *it << endl;
    }
        
    auto it = myset.begin();
    myset.insert(it, 100); // it is just a hint, if right, insert is O(1), else O(log(n))

    // Modiying an existing element is NOT allowed.
    // Can not assign a value like *it = 10, it will mess up the ordering in RB tree
    // Can not update a set's element since it may change thee order of nodes.
    // You must erase and re-insert if update is required.
    // For such modify use cases, consider a map instead of a set.
}

void test_set_erase(set <int> &myset) {
  auto it = myset.begin();
  myset.erase(it); // erase(position), amortized constant.
  myset.erase(70); // erase(val), logarithmic in container size.
  // Lower bound is the pointer to first >= occurence
  auto itlow = myset.lower_bound(30);
  // Upper bound is the pointer to first > occurence
  auto itup = myset.upper_bound(60);
  myset.erase(itlow, itup); // erase(first,last), linear in the distance between first and last.
}

void test_set_print(set <int> &myset) {
  std::cout << "myset contains:";
  for (auto i : myset)
    cout << ' ' << i;
  cout << '\n';
}

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

void test_set_init () {
  std::set<int> first;                           // empty set of ints

  int myints[]= {10,20,30,40,50};
  std::set<int> second (myints,myints+5);        // range

  std::set<int> third (second);                  // a copy of second

  std::set<int> fourth (second.begin(), second.end());  // iterator ctor.

  std::set<int,classcomp> fifth;                 // class as Compare

  bool(*fn_pt)(int,int) = fncomp;
  std::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare
}

void learn_set (void) {
 
  test_set_init();

  set<int> myset;

  test_set_insert(myset);

  test_set_find_count(myset, 20);

  test_set_erase(myset);

  test_set_print(myset);
  
  // clear(): removes all elements from the set container (which are destroyed), leaving the container with a size of 0.
  myset.clear();
  std::cout << "myset size: " << myset.size() << '\n';
}

void learn_multiset (void) {
 
  multiset<int> myset;

  for (int i=10; i>0; i--) 
    myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

  myset.insert(30);
  myset.insert(30);
  myset.insert(80);
  myset.insert(60);

  // Lower bound is the pointer to first >= occurence
  auto itlow = myset.lower_bound(30);

  // Upper bound is the pointer to first > occurence
  auto itup = myset.upper_bound(30);

  myset.erase(itlow, itup); 

  std::cout << "Multiset myset contains:";
  for (auto i : myset)
    cout << ' ' << i;
  cout << '\n';
}

int main () {
 
  learn_set();
  learn_multiset();

  return 0;

}
