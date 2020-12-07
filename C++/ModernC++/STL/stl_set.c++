// set::lower_bound/upper_bound
#include <iostream>
#include <set>

using namespace std;

// sets are implemented as a BST (default sorting is < )
// No duplicates allowed - if you need duplicates, use multiset
// Only insert and erase  and find- NO modify 
// Can not update an element - use map instead if u want to update
// No need to sort every time after every insert (which is required for a vector)
// For sort(v.begin(), v.end()) it takes nlogn. For set, it's just logn.


// multi set allows duplicates
// unordered_set is simply a hash table

void test_set (set <int> &myset) {

    auto it = myset.begin();

    pair<set<int>::iterator, bool> iret;
    iret = myset.insert(20);

    if (iret.second == false)  // duplicates not allowed, so no new elem inseted
        it = iret.first; // it now points to 30

    myset.insert(it, 100); // it is just a hint, if right, insert is O(1), else O(log(n))

    // Can not assign a value like *it = 10, it will mess up the ordering in tree
    myset.erase(it); //it still pointed to 30, so erase that
    myset.erase(70);
}

void learn_set (void) {
 
  set<int> myset;

  for (int i=1; i<10; i++) 
    myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

  test_set(myset);

  myset.insert(30);
  myset.insert(30);

  // Lower bound is the pointer to first >= occurence
  auto itlow = myset.lower_bound(30);

  // Upper bound is the pointer to first > occurence
  auto itup = myset.upper_bound(60);

  myset.erase(itlow, itup); 
  if (myset.find(80) != myset.end()) {
    cout << " Found 80" << endl;
  }

  std::cout << "myset contains:";
  for (auto i : myset)
    cout << ' ' << i;
  cout << '\n';

  // Can not update a set element since it may change thee order of nodes.
  // You must erase and re-insert if update is required.
  // That's why use map instead of a set 

  test_set(myset);
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
