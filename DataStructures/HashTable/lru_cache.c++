#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

/*
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

    LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
    int get(int key) Return the value of the key if the key exists, otherwise return -1.
    void put(int key, int value) Update the value of the key if the key exists. 
    Otherwise, add the key-value pair to the cache. 
    If the number of keys exceeds the capacity from this operation, evict the least recently used key.

    get and put should be in O(1) time complexity
*/

using namespace std;
/*
// Very clear logic ->
int size;
list<int> lru;                              //  holds keys : front() has MRU ... LRU at the back()
unordered_map<int, list<int>::iterator> mp; // key -> iterator
unordered_map<int, int> kv;                 // key -> value

LRUCache(int capacity) : size(capacity) {}
int get(int key) {
    if (kv.count(key) == 0) return -1;
    updateLRU(key);
    return kv[key];
}
void put(int key, int value) {
    if (kv.size() == size && kv.count(key) == 0)
        evict();
    updateLRU(key);
    kv[key] = value;
}
void updateLRU(int key) {
    if (kv.count(key)) 
        lru.erase(mp[key]);
    lru.push_front(key);
    mp[key] = lru.begin();
}
void evict() {
    mp.erase(lru.back());
    kv.erase(lru.back());
    lru.pop_back();
}
*/

class LRUCache {
    int cap;
    unordered_map <int, pair<int, list <int>::iterator>> hashtable; // key <--> { data, itr}
    list <int> cache; // key @ itr
    
public:
  LRUCache(int capacity) {
    cap = capacity;
  }
  
  int get(int key) {
    if (hashtable.find(key) == hashtable.end()) 
      return -1;
    
    cache.erase(hashtable[key].second);
    cache.push_back(key);
    hashtable[key].second = --cache.end();
    
    return hashtable[key].first;
  }
  
  void put(int key, int value) {
    if (hashtable.find(key) != hashtable.end()) {
      // found in cache - update the value, and LRU location
      
      cache.erase(hashtable[key].second);
      cache.push_back(key);
      hashtable[key].second = --cache.end();
      
      hashtable[key].first = value;
      return;
    }
    
    // Not found, allocate
    if (cache.size() == cap) {
      // evict the front
      hashtable.erase(cache.front());
      cache.pop_front();
    }            
    cache.push_back(key);
    hashtable[key] = make_pair(value, --cache.end());
    
  }
};

int main () {

  LRUCache *lRUCache = new LRUCache(2);
  int val;

  lRUCache->put(1, 1); // cache is {1=1}
  lRUCache->put(2, 2); // cache is {1=1, 2=2}
  val = lRUCache->get(1);    // return 1
  cout << "val : " << val << endl;

  lRUCache->put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  val = lRUCache->get(2);    // returns -1 (not found)
  cout << "val : " << val << endl;

  lRUCache->put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  val = lRUCache->get(1);    // return -1 (not found)

  cout << "val : " << val << endl;

  val = lRUCache->get(3);    // return 3
  cout << "val : " << val << endl;

  val = lRUCache->get(4);    // return 4
  cout << "val : " << val << endl;
  
  return 0;
}



