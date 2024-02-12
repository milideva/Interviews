#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// In an array a[], find elements, that satisfy x + y + z = w
// x = a[i]; y = a[j]; z = a[k]; w = a[n]
// i < j < k < n
// find all such sets, sorting is NOT allowed.

// g++ -std=c++20 3sum_noSort.c++

// Time:  O(n ^2)
// Space: O(∣ans∣)
    
class Solution {

    // hash table elem2index :  a[i] -> i
    unordered_map<int, int> elem2index;
    // hash table sum2y : x+y -> y
    unordered_map<int, int> sum2y;

    vector<vector<int>> result;

public:
    vector<vector<int>> find_triplet_sum(vector<int> &v) {
        for (int i = 0; i < v.size(); i++) {
            elem2index.insert({v[i], i});
        }

        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                int sum = v[i] + v[j];
                sum2y.insert({sum, v[j]});
            }
        }

        // find w - z in sum2y, if it's found, it means w -z = x + y.
        // now check i < j < k < n

        for (int i = 0; i < v.size() - 2; i++) {
            for (int j = i + 1; j < v.size(); j++) {
                int sub = v[j] - v[i];
                auto got = sum2y.find(sub);
                if (got == sum2y.end()) {
                    continue;
                }
                int iw = j;
                int iz = i;

                int y = got->second;
                auto itry = elem2index.find(y);
                if (itry == elem2index.end()) {
                    continue;
                }
                int iy = itry->second;

                int x = sub - y;
                auto itrx = elem2index.find(x);
                if (itrx == elem2index.end()) {
                    continue;
                }
                int ix = itrx->second;
                if (ix < iy && iy < iz && iz < iw) {
                    vector<int> oneresult = {x, y, v[i], v[j]};
                    result.push_back(oneresult);
                }
            }
        }
        return result;
    }
};

void test_3sum(vector<int> &v) {
    class Solution sol;
    vector <vector <int>> vv = sol.find_triplet_sum(v);

    for (auto v : vv) {
        for (auto elem : v) 
            cout << elem << " ";
        cout << endl;
    }
}

int main() {
    vector<int> test_array = {56, 4, 5, 1, 8, 15, 56, 23, 32, -4, -3, -7, -14, 0};
    test_3sum(test_array);
    return 0;
}
