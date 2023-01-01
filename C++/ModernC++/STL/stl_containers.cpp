#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <list>
#include <array>
#include <set>
#include <unordered_set>

#include <map>
#include <unordered_map>

using namespace std;

// C++ : data struct aka container.

// g++ -std=c++17 stl_containers.cpp
// g++ -std=c++2a stl_containers.cpp

// https://en.cppreference.com/w/cpp/container

// 1. 
// Sequence containers : 
// array, vector, dequeue, 
// list (doubly-linked list), forward list (sinlgy-linked list in forward direction onlu).
// Sequence containers implement data structures which can be accessed sequentially.


// Container adaptors :
// stack (LIFO), queue (FIFO), priority_queue


// 2.
// Associative containers : like a binary search tree - always ordered (actually implemented as RB tree)
// always sorted.  takes O(logn) time for insertion/deletion/search.
// 2a) set, multiset  = can store single item aka "value", use multi for allowing duplicate items
// In Section 3 below : unordered_set is a hash table of values (no ordering)
// Primary application of set is trees, such as BST
// 2b) map, multimap store a pair {key, value} : can map itemA (key) to itemB (value), use multi for allowing duplicate items
// In Section 3 below : unordered_map is a hash table of pair {key, val} (no ordering)

// find is faster than array but slower than unordered_set or unordered_map which are Hash Tables
// Modifying an element, would invalidate ordering. Hence it must be erased first and then reinserted with new value.

/*
The primary reason to use a set or a multiset is when you need to keep your
data in sorted order. The underlying data structure for sets and multisets is
the balanced binary tree, which means that keeping the data in order is very
efficient. However, using binary trees also creates a problem because you can’t
change the value of an element in place because doing so would invalidate the
ordering. So, making changes involves removing an element from the container
and then inserting a new element. This is more inefficient than doing so in
another container so you will want to choose a different container if you need
to make lots of changes to the data in your application.
*/

// 3.
// Unordered containers (implemented as a hash table - hence O(1) to access)
// Hash table entries are 'unordered'
// Unordered set, Unordered multiset, 
// Unordered map, Unordered multimap


/* 
	Iterators connect algorithms to containers/
	Thus same algorithm can work on different types of containers
*/

/*
	***************************
	List - double linked list - bad cache performance
	http://www.cplusplus.com/reference/list/list/
	***************************
*/
void show_list (list <int> ls) {

	list <int>::const_iterator it;

	cout << endl << "\n\n\n\n ********** \n\n Show list: " ;

	for (it = ls.cbegin(); it != ls.cend(); it++)
			cout << "\t" << *it;
	cout << endl;

	ls.sort();

	cout << endl << "Sorted list : ";

	for (auto i : ls) { // C++11 way
		cout << i << " ";
	}

    cout << "\nsize() : " << ls.size(); 
    cout << "\nmax_size() : " << ls.max_size(); 
}

// Properties of a list
// fast insert/remove at ANY point using iterator : O(1)
// slow insert/remove at the beginning or in the middle : O(n)
// slow search : O(n)
// NO random access => no [] operator
// Killer use case : splice !
// l1.splice(itr1, l2, itr2_b, itr2_e); // O(1) - constant time, no matter how big (itr2_b, itr2_e) is!
// No other container can do splice.

void test_list (void) {

	list<int> lst =  { 900, 90, 9000, 999};
	lst.push_front(99);
	lst.push_back(909);
	show_list(lst);

	cout << "\n pop_front() : "; 
    lst.pop_front(); 
    cout << "\n size() after pop_front(): " << lst.size(); 

    cout << "\n pop_back() : " << lst.back(); 
    lst.pop_back(); 
    cout << "\n size() after pop_back(): " << lst.size(); 

    show_list(lst);

    list<int>::iterator itr = find(lst.begin(), lst.end(), 900);
    lst.insert(itr, 901);
    itr++;
    lst.insert(itr, 899);
    itr--;
    lst.erase(itr);
   	show_list(lst);
}

// Pass by reference
void increment_dq (deque <int> & dq) {
  
    cout << "Incementing a deque" << endl;
    for (auto &i : dq)  // Note reference i.e. &i for modifying value
        i++;
}

/*
	***************************
	Deque - can grow in front or in end
	http://www.cplusplus.com/reference/deque/deque/
	***************************
*/
void show_deque (deque <int> dq) {

	deque <int>::const_iterator it;

	cout << endl << "\n\n\n\n ********** \n\n Show Deque: " ;

	for (it = dq.cbegin(); it != dq.cend(); it++)
			cout << "\t" << *it;
	cout << endl;

	deque <int>::iterator ditr1 = dq.begin();
	auto ditr2 = dq.end();

	sort(ditr1, ditr2);

	cout << endl << "Sorted dequeue : ";

	for (auto i : dq) { // C++11 way
		cout << i << " ";
	}

    increment_dq(dq);

    for (auto i : dq) { // C++11 way
        cout << i << " ";
    }

    cout << "\nsize() : " << dq.size(); 
    cout << "\nmax_size() : " << dq.max_size(); 
}

// Properties of Deque
// fast insert/remove at the beginning as well as end : O(1)
// slow insert/remove at the beginning or in the middle : O(n)
// slow search : O(n)
void test_deque (void) {

	deque<int> deq =  { 600, 60, 6000, 666};
	deq.push_front(6666);
	deq.push_back(66);
	show_deque(deq);

	cout << "\n pop_front() : "; 
    deq.pop_front(); 
    cout << "\n size() after pop_front(): " << deq.size(); 

    cout << "\n pop_back() : " << deq.back(); 
    deq.pop_back(); 
    cout << "\n size() after pop_back(): " << deq.size(); 

    show_deque(deq);
}

/*
	***************************
	vector (dynamic array) - can grow only at the end
	http://www.cplusplus.com/reference/vector/vector/vector/
	***************************
*/
void show_vector (vector <int> vec) {

	cout << endl << "\n\n ********** \n\n Show vector: " ;
	
	vector <int>::const_iterator cit;

	for (cit = vec.cbegin(); cit != vec.cend(); cit++)
			cout << "\t" << *cit;
	cout << endl;

	vector <int>::iterator ditr1 = vec.begin(); // points to first
	vector <int>::iterator ditr2 = vec.end(); // points outside last

	// vec is half open [begin, end)
	sort(ditr1, ditr2);

	cout << endl << "Sorted vector: ";

	for (auto i : vec) { // C++11 way
		cout << i << "\t ";
	}

    cout << "\nsize() : " << vec.size(); 
    cout << "\nmax_size() : " << vec.max_size(); 
}


// Properties of vector
// fast insert/remove at the end : O(1)
// slow insert/remove at the beginning or in the middle : O(n)
// slow search : O(n)

void test_vector (void) {
	vector <int> vec;
	// dynamic array.
	size_t sz = vec.capacity();

	vec.push_back(444);

	if (sz != vec.capacity()) {
		sz = vec.capacity();
		cout << "capacity changed: " << sz << '\n';
	} else {
		cout << "capacity unchanged: " << sz << '\n';
	}

	vec.push_back(44);

	if (sz != vec.capacity()) {
		sz = vec.capacity();
		cout << "capacity changed: " << sz << '\n';
	} else {
		cout << "capacity unchanged: " << sz << '\n';
	}

	vec.push_back(404);

	if (sz != vec.capacity()) {
		sz = vec.capacity();
		cout << "capacity changed: " << sz << '\n';
	} else {
		cout << "capacity unchanged: " << sz << '\n';
	}

	vec.push_back(44404);
	if (sz != vec.capacity()) {
		sz = vec.capacity();
		cout << "capacity changed: " << sz << '\n';
	} else {
		cout << "capacity unchanged: " << sz << '\n';
	}

	//vec.push_front(100); // can push only at the end. not in the beginning.
	// dequeue can do front as well as back.
    vec[1] = 1; // however, you can do random access like an array.


    show_vector(vec);

    cout << "\n pop_back() : " << vec.back(); 
    vec.pop_back(); 
    cout << "\n size() after pop_back(): " << vec.size(); 


	cout << vec[3] << endl; // no range check - prints garbage
	//cout << vec.at(3) << endl; // throw range_error exception if out of range

	show_vector(vec);

	vector<int> vec2(vec); // copy constructor.
	vec.clear(); // vec.size() = 0 now. removes all elements.
	vec2.swap(vec); //vec2 is empty now and vec is back.


}

// Using a vector as a heap 
// make_heap() -> heapify current array/vector
// pop_heap() (moves it to end) must be used with pop_back()
// push_back() must be used with push_heap()

void test_heap (void) {
  int myints[] = {10,20,30,5,15};
  std::vector<int> v(myints,myints+5); // array to vector

  std::make_heap (v.begin(),v.end()); // vector to heap
  std::cout << "initial max heap   : " << v.front() << endl; // max heap root is at front()

  std::pop_heap (v.begin(),v.end()); // remove top of heap - it moves it to the end
  v.pop_back(); // remove it from end as well
  std::cout << "max heap after pop : " << v.front() << endl; // new top is at the front

  v.push_back(99); // adds to the end of the vector 
  std::push_heap (v.begin(),v.end()); // push to the heap and heapify
  std::cout << "max heap after push: " << v.front() << '\n'; // new top

  std::sort_heap (v.begin(),v.end());

  std::cout << "final sorted range :";
  for (unsigned i=0; i<v.size(); i++)
    std::cout << ' ' << v[i];

  std::cout << '\n';

}


void test_array () {
	// Limitation 1 => constant size
	array<int, 3> a3 = { 3, 4, 5};
	a3.begin();
	a3.end();
	a3.size();

	// Limitation 2 =>  a4 can not be passed in place of a3 because their types are DIFFERENT !
	array<int, 4> a4 = { 3, 4, 5};

}



// Associative containers
// Always sorted. default criteria is <
// No push_back(), no push_front()

void show_set (set <int> st) 
{

	cout << "\n\n ********** Show Set: " << endl ;

	for (auto i:st) { // C++11 way
		cout << i << "\t ";
	}

    cout << "\nsize() : " << st.size() << endl; 
	
}

void erase_from_set (set <int> &numbers, int remove_me) {
  int count = numbers.erase(remove_me);
  cout << count << " element was removed." << endl << endl;
  for (const int n : numbers) {
    cout << n << " ";
  }

  // 2nd method to remove, in which we've a position
  // Iterator tells the position to remove
  numbers.insert(remove_me);

  auto iter = numbers.begin();
  while (*iter != remove_me) {
    iter++;
  }
  numbers.erase(iter);
  cout << endl << "element was removed " << remove_me << endl;
  show_set(numbers);

}

void print_set (const set<int, greater<int>> st) {
  cout << "Greater than walah set " << endl; 
  for (const int n : st) {
    cout << n << " ";
  }
}

void build_set (set<int, greater<int>> &st) {
  srand(time(0));
  for (int i = 1; i <= 25; i++) {
    st.insert(rand() % 100 + 1);
  }
}


/* Set
    Like a binary search tree 
    Always ordered
	No duplicates
	Traversing is slow (cache locality issue)
	no random access, no [] operator
	*/
void test_set ()
{

	set<int> myset;


    // Note always check return value of insert - it can fail for duplicates
	myset.insert(77); 
	myset.insert(67); // myset = {67, 77}
	myset.insert(57); // myset = {57, 67, 77}
	myset.insert(77); // myset = {57, 67, 77} -> no new element inserted
	myset.insert(47); // myset = {47, 57, 67, 77}
	myset.insert(7777); // myset = {47, 57, 67, 77, 7777}
	myset.insert(777); // myset = {47, 57, 67, 77, 777, 7777}


	show_set(myset);

	set<int>::iterator it;

	it = myset.find(57); // Olog(n)

    erase_from_set(myset, 77);

/*
    return value is a pair structure where the first field is the insertion
    position and the second field is a boolean value showing the success or failure
    of the insertion.
*/
	pair<set<int>::iterator, bool> ret_pair;
	ret_pair = myset.insert(67);
	if (ret_pair.second == false)
		it = ret_pair.first;

    ret_pair = myset.insert(59);
    cout << endl << *ret_pair.first << " set==> " << ret_pair.second << endl;

	// *it = 999999; // not allowed. it's read-only, element can not be modified with iterator.
	// otherwise it can get out of order, hence not allowed.
	// what is the use of iterator then?

	myset.insert(it, 999);// position can not be decided by it, it's decided by the value being inserted.
	show_set(myset);

	myset.erase(it); // it points to 67 - will be deleted, used as hint to insert or delete.

	show_set(myset);


    set<int, greater<int>> numbers;
    build_set(numbers);
    print_set(numbers);
}



void show_mset (multiset <int> mst) 
{

	cout << endl << "\n\n ********** \n\n Show MultiSet: " ;

	for (auto i : mst) { // C++11 way
		cout << i << "\t ";
	}

    cout << "\nsize() : " << mst.size(); 
	
}

// Same as set except multiset allows duplicates

void test_multiset () 
{

	multiset<int> mymset;

	mymset.insert(77); 
	mymset.insert(67); // myset = {67, 77}
	mymset.insert(57); // myset = {57, 67, 77}
	mymset.insert(77); // myset = {57, 67, 77, 77 } new duplicate element inserted
	mymset.insert(47); // myset = {47, 57, 67, 77, 77}
	mymset.insert(7777); // myset = {47, 57, 67, 77, 77, 7777}
	mymset.insert(777); // myset = {47, 57, 67, 77, 77, 777, 7777}

	show_mset(mymset);

}


void show_map (map <char, int> mymap) {

	cout << endl << "\n\n ********** " << endl << "Show Map: " << endl;

	for (auto p:mymap) {  // C++11 pair that holds key and value
		cout << p.first << " $$==> " << p.second << endl;
	}

    for (auto [key, val] : mymap) { // C++17 onwards
        cout << key  << " ==> " << val << endl;
    }

}

// Associative containers. map/multimap
// set : Always sorted. default criteria is <
// map allows you to sort on a key instead of a <
// no duplicate keys

void test_map () {
	map <char, int> mymap;
	mymap.insert(pair<char, int> ('a', 100));
	mymap.insert(make_pair('z', 2600)); // make_pair : infers typing,

    mymap['c'] = 27;

	map <char, int>::iterator it = mymap.begin();
	mymap.insert(it, make_pair('c', 300)); // it is a hint

	it = mymap.find('z'); // Olog(n)

	show_map(mymap);
}


void show_unordered_set (unordered_set<string> uset) {

	cout << endl << "\n\n ********** " << endl << "Show unordered_set: " << endl;

	for (auto itr:uset)
		cout << itr << endl;

	// load = #elements/#buckets
	cout << "Load factor: " << uset.load_factor() << endl;
	string str = "red";
	cout << str << " is in bucket#: " << uset.bucket(str) << endl;
	cout << "Total #buckets: "  << uset.bucket_count() << endl;


}

// Unordered associative containers
// unordered set or multiset
// unordered map or multimap
// Internally Hash table gives buckets which has entries (linked list)
// Fastest search or insert at any place : O(1)
// associative containers takes O(Log(n)), vector/deque takes O(n)
// list takes O(1) to insert, O(n) to search

void test_unordered_set (void) {


	unordered_set<string> uset = {"red", "blue", "green"};
	unordered_set<string>::const_iterator itr = uset.find("blue"); // O(1) 

	if (itr != uset.end())
		cout << "Found:" << *itr << endl;
	uset.insert("yellow");
	uset.insert("indigo");
	uset.insert("purple");

	show_unordered_set(uset);
}



void show_unordered_map (unordered_map<char, string> umap) {

	cout << endl << "\n\n ********** " << endl << "Show unordered_map: " << endl;

    // {key, value} pair accessed as {first, second} in a map
	for (auto itr:umap)
		cout << itr.first  << " ==> " << itr.second << endl;

}

// Associative array - it's a store of {key, value} pair 
// Each element is a {key, value} pair accessed as {first, second} in a map
// unordered_map may degrade to O(n)
// can't use multimap and unordered_multimap as they dont have unique key and no []
void test_unordered_map (void) {

	unordered_map <char, string> umap = { {'R', "red"}, {'B' , "blue"}, {'G', "green"} };


	cout << endl << "\n\n ********** " << endl << "test unordered_map: " << endl;

	cout << umap['B'] << endl; // no range check
	cout << umap.at('B') << endl; // range check 

	vector<int> vec = { 5, 1, 44 };
	//vec[5] = 1; // NO compilation error

	umap['I'] = "Indigo"; // inserting
	umap.insert(make_pair('Y', "yellow"));

	show_unordered_map(umap);

	cout << "\n\ninserting black" << endl;

	umap.insert(make_pair('B', "black")); // fail to modify !!!
	show_unordered_map(umap);

	cout << "\n\nAgain inserting black" << endl;

        // search for a key in map 
        if (umap.find('Z') == umap.end()) {
          cout << 'Z' << " Not found ... inserting " << endl;
          umap['Z'] = "zebra";
        }
	umap['B'] = "black"; // succeed to modify
	show_unordered_map(umap);

}

// Array based containers such as vector or deque, can invalidate pointers or iterators or references.
// Node based containers do not have such a problem.

void test_pointers (void) {

	vector<int> vec = { 10, 20, 30};
	int *p = &vec[2]; // points to 30.

	cout << "vec[2] = " << *p << endl;
	vec.insert(vec.begin(), 0);
	vec.insert(vec.begin(), 10);

/* 
As std::vector is a dynamic data structure it provides the ability to resize itself. 
The internal buffer of vector is implemented as an array, which is stored in contiguous memory. 
When adding a new element to the vector, it may have to resize itself to accommodate this new element. 
In doing so it may have to completely relocate the internal array buffer to find some area of contiguous 
memory that is large enough. Thus rendering the old pointer invalid.
*/
	cout << "vec[2] = " << *p << endl;
}

int main () {

// Sequence containers 
	test_vector();

	test_deque();

	test_list();

	test_array();

//  Associative containers 
	test_set();

	test_multiset();

	test_map();

	test_unordered_set();

	test_unordered_map();

	test_pointers();
}
