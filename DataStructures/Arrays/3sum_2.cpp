#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// In an array a[], find elements, that satisfy x + y + z = w
// x = a[i]; y = a[j]; z = a[k]; w = a[n]
// i < j < k < n
// find all such sets

// hash table elem2index :  a[i] -> i
unordered_map<int, int> *build_elem2index_hash (vector <int> &v) {
    unordered_map<int, int> *elem2index = new unordered_map<int, int>;
    for (int i = 0; i < v.size(); i++) {
        elem2index->insert({v[i], i});
    }
    return elem2index;
}

// hash table sum2y : x+y -> y
unordered_map<int, int> *build_sum2y_hash (vector <int> &v) {
    unordered_map<int, int> *sum2y = new unordered_map<int, int>;
    for (int i = 0; i < v.size()-1; i++) {
       for (int j = i+1; j < v.size(); j++) {
            int sum = v[i] + v[j];
            sum2y->insert( {sum, v[j]} );
        }
    }
    return sum2y;
}

// find w - z in sum2y, if it's found, it means w -z = x + y. 
// now check i < j < k < n 
vector<vector<int>> check_w_minus_z (unordered_map <int, int> *sum2y, vector <int> &v, unordered_map<int, int> *elem2index) {
    vector<vector <int>> result;
    for (int i = 0; i < v.size()-2; i++) {
        for (int j = i+1; j < v.size(); j++) {
            int sub = v[j] - v[i];
            unordered_map<int, int>::const_iterator got = sum2y->find(sub);                   
            if (got == sum2y->end()) {
                continue;
            }
            int iw = j;
            int iz = i;

            int y = got->second;
            unordered_map<int, int>::const_iterator itry = elem2index->find(y);
            if (itry == elem2index->end()) {
                continue;
            }
            int iy = itry->second;

            int x = sub - y;
            unordered_map<int, int>::const_iterator itrx = elem2index->find(x);
            if (itrx == elem2index->end()) {
                continue;
            }
            int ix = itrx->second;
            if (ix < iy && iy < iz && iz < iw) {
                vector <int> oneresult = {x, y, v[i], v[j]};
                result.push_back(oneresult); 
            }
        }
    }
    return result;
    
}

void test_3sum (vector <int> &v) {
    unordered_map<int, int> *elem2indexHash = build_elem2index_hash(v);
    unordered_map<int, int> *sum2y = build_sum2y_hash(v);
    vector<vector <int>> result = check_w_minus_z(sum2y, v, elem2indexHash);

    for (auto itr : result) {
       vector <int> oneresult = itr;
        for (auto itr2 : oneresult) 
            cout << itr2 << " ";
        cout << endl;
    }

}

int main () {
    vector <int> test_array = { 56, 4, 5, 1, 8, 15, 56, 23, 32, -4, -3, -7, -14, 0 };
    test_3sum(test_array); 
    return 0;
}
