#include <vector>
#include <iostream>
#include <unordered_map>
#include <string> 

using namespace std;

/*
    Given an array of numbers, non negative, no duplicates, sorted.
    Find number of subsets that add up to a given total
*/
int count_sum_nums (vector <int> arr, int total, int index) {
    if (index >= arr.size()) return 0;
    if (arr[index] < 0) return 0;
    if (index < 0) return 0;
    if (total < 0) return 0;

    cout << "arr[" << index << "] = " << arr[index] << " total: " << total << endl;
    if (total == 0) return 1; // empty set is 1 soln
    if (index == 0 && arr[index] == total) return 1;

    if (arr[index] > total) {
        // too big, total remains unchanged go to next index
        return count_sum_nums(arr, total, index-1);
    }

    // a set including current number, and a set excluding current number
    return count_sum_nums(arr, total-arr[index], index-1) + count_sum_nums(arr, total, index-1);
}

int count_sum_nums_dp (vector <int> arr, int total, int index, unordered_map <string, int> &ht) {
    if (index >= arr.size()) return 0;
    if (arr[index] < 0) return 0;
    if (index < 0) return 0;
    if (total < 0) return 0;

    string str = to_string(total) + '+' + to_string(index);

    if (total == 0) {
      ht[str] = 1;
      return 1; // empty set is 1 soln
    }
    if (index == 0 && arr[index] == total) {
      ht[str] = 1;
      return 1;
    }

    if (arr[index] > total) {
        // too big, total remains unchanged go to next index
        int cnt = count_sum_nums(arr, total, index-1);
        ht[str] = cnt;
        return cnt;
    }

    if (ht[str]) {
      cout << " Dp found " << str << endl;
      return ht[str];
    }
    
    // a set including current number, and a set excluding current number
    int cnt = count_sum_nums_dp(arr, total-arr[index], index-1, ht) + count_sum_nums_dp(arr, total, index-1, ht);

    if (cnt) {
      ht[str] = cnt;
    }
    return cnt;
}

int count_sum_nums_dp_driver (vector <int> arr, int total, int index) {
  unordered_map <string, int> ht;
  return count_sum_nums_dp(arr, total, index, ht);
}

int main () {

    vector <int> a{2,  4, 6, 10};

    int total = 16;

    int cnt = count_sum_nums(a, total, a.size()-1);
    cout << "count:" << cnt << " sum:" << total << endl;

    cnt = count_sum_nums_dp_driver(a, total, a.size()-1);
    cout << "dp count:" << cnt << " sum:" << total << endl;

    return 0; 
}
