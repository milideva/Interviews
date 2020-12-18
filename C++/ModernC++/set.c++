//#include <bits/stdc++.h> 
#include <set>
#include <iostream>
#include <vector>

using namespace std;
  
typedef pair<int, int> pairs; 
  
void display(const set<pairs>& s)  { 
  bool found = false; 
  
  // range-based for loop 
  for (auto const &x : s) { 
    found = true; 
    cout << "(" << x.first << ", "
         << x.second << ")"
         << " "; 
  } 
  cout << endl;
  if (not found) { 
    cout << "No valid pair\n"; 
  } 
}

int main() { 
  vector<int> v{ 2, 3, 18, 8, 10, 8, 2 };  
  set<pairs> s; 
  
  for (int i = 0; i < v.size() - 1; i++) { 
    for (int j = i + 1; j < v.size(); j++) { 
      // check for even number 
      if (v[i] % 2 == 0 && v[j] % 2 == 0) { 
        
        // makes pairs of even numbers 
        pairs x = make_pair(v[i], v[j]); 
        
        // inserts into the set 
        s.insert(x); 
      } 
    } 
  } 
  
  display(s); 
  
  s.clear(); 
  return 0;
} 
