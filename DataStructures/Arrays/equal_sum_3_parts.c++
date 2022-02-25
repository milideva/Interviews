#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*

1013. Partition Array Into Three Parts With Equal Sum

Given an array of integers arr, return true if we can partition the array into three non-empty parts with equal sums.

Formally, we can partition the array if we can find indexes i + 1 < j with (arr[0] + arr[1] + ... + arr[i] == arr[i + 1] + arr[i + 2] + ... + arr[j - 1] == arr[j] + arr[j + 1] + ... + arr[arr.length - 1])

 

Example 1:

Input: arr = [0,2,1,-6,6,-7,9,1,2,0,1]
Output: true
Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1
Example 2:

Input: arr = [0,2,1,-6,6,7,9,-1,2,0,1]
Output: false
Example 3:

Input: arr = [3,3,6,5,-2,2,5,1,-9,4]
Output: true
Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4

*/

class Solution {
public:
    /*
        If we have three parts with the same sum, what is the sum of each? 
        If you can find the first part, can you find the second part?
    */
    bool canThreePartsEqualSum(vector<int>& arr) {
        int sz = size(arr);
        if (sz == 0) 
            return false;
        int sum = 0;
        for (auto i : arr) {
            sum += i;
        }
        if (sum % 3) return false;
        int target = sum / 3;
        
        int numSums = 0;
        int currSum = 0;
        for (auto i = 0; i < sz; i++) {
            currSum += arr[i];
            if (currSum == target) {
                numSums++;
                currSum = 0;
                if (numSums == 2 && i < sz - 1) {
                    return true;
                }
            }
        }
        if (numSums == 3) {
            return true;
        }
        return false;
    }
};

void printVec (vector <int> &vec, string str) {
  cout << str;
  for (auto i: vec) {
    cout << i << " ";
  }
  cout << endl;
}

int main () {
  vector <int> arr {0,2,1,-6,6,-7,9,1,2,0,1};
  printVec(arr, "Array: ");

  class Solution sol;
  
  auto ret = sol.canThreePartsEqualSum(arr);
  cout << "canThreePartsEqualSum:" << ret << endl;

  arr = {3,3,6,5,-2,2,5,1,-9,4};
  printVec(arr, "Array: ");

  ret = sol.canThreePartsEqualSum(arr);
  cout << "canThreePartsEqualSum:" << ret << endl;

  return 0;
}
