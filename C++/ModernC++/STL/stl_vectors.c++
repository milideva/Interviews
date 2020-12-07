#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void print_vector (vector <int> &v) {
    // By value  
    for (auto it : v) 
        cout << it << " ";

    cout << endl;
    return;

    // By reference - if you want to modify
    // For proxy iterators such as bool, we need to use &&it
    for (auto &it : v)
        it += 1;

    // reverse order
    for (auto itr = v.rbegin(); itr != v.rend(); itr++) 
        cout << *itr << " ";

    for (auto &it : v) 
        it -= 1;

    cout << endl;
}

/*

Given an array of integers and an integer k, 
you need to find the number of unique k-diff pairs in the array. 
Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k.

*/
int findPairs(vector<int>& nums, int k) {
    int count = 0;
    sort(nums.begin(), nums.end());
    cout << "findPairs() after sorting" << endl;

    print_vector(nums);        

    for (auto it = nums.begin(); it != nums.end(); it++)  {

        auto src = *it;
            
        auto itfind = find(it+1, nums.end(), k+src);
        if (itfind != nums.end()) {
            count++;
            cout << "Pair " << *it << " " << *itfind << endl; 
            nums.erase(itfind);
        }
    }
    return count;
}


void test_vector (vector <int> &v) {
    v.push_back(110);
    v.insert(v.begin(), 0);

    v.push_back(100);
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(110);

    cout << "Vector is unsorted : " << endl;
    print_vector(v);

    sort(v.begin(), v.end());

    cout << "Vector after sorting : " << endl;
    print_vector(v);

    // Lower bound is the pointer to first >= occurence
    auto itlow = lower_bound(v.begin(), v.end(), 10);

    // Upper bound is the pointer to first > occurence
    auto itup = upper_bound(v.begin(), v.end(), 10);
    cout << "#duplicates of 10 : " << itup - itlow << endl;

    auto it1 = find(v.begin(), v.end(), 40);
    auto it2 = find(v.begin(), v.end(), 70);

    v.erase(it1, it2); // erase a range, excludes last iter
    v.erase(v.begin());
    v.erase(v.end()-1);
    print_vector(v);
}

int main (void) {
    //vector <int> v =  { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    vector <int> v =  { 3, 1, 4, 1, 5 };
    test_vector(v);
    int k = 2;
    int ret = findPairs(v, k);
   cout <<"#Pairs : " << ret << " k: " << k << endl; 

}

