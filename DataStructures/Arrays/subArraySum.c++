
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

/*

523. Continuous Subarray Sum

Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.

A good subarray is a subarray where:

its length is at least two, and
the sum of the elements of the subarray is a multiple of k.
Note that:

A subarray is a contiguous part of the array.
An integer x is a multiple of k if there exists an integer n such that x = n * k. 
0 is always a multiple of k.
 

Example 1:

Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
Example 2:

Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
Example 3:

Input: nums = [23,2,6,4,7], k = 13
Output: false

*/
class Solution {
  
  /*
    This is a variation of 2-sum problem with some math added.
    
    find i, j s.t. sum(nums[i..j]) % k == 0
    accum[0..i] = sum(nums[0..i])
    sum[i..j] = accum[j] - accum[i]
    accum[i] = a * k + r1 
    accum[j] = b * k + r2
    accum[j] - accum[i] = (a - b) * k + r2 - r1
    
    (a - b) * k is already a multiple of k
    r1 and r2 are between 0 .. k, if we want accum[j] - accum[i] to be a multiple of k
    only way to do that is r1 = r2
    
    Instead of storing accum[i], what we want is r[i] = sum[0..i] % k,
    thus sum[i..j] is a multiple of k if r[j] = r[i]
    To find such a collision, store sum[arr(0..i)] % k ==> i mapping
    
  */
    
public:
  // Brute force : Time Limit Exceeded O(n^3) 
  bool checkSubarraySumTLE(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size() - 1; i++) {
      for (int j = i+1; j < nums.size(); j++) {
        int sum = 0;
        for (int k = i; k <= j; k++)
          sum += nums[k];
        if (sum == target or (target && sum % target == 0))
          return true;
      }
    }
    return false;
  }
  // O(n) : This is a variation of 2-sum problem with some math added.
  bool checkSubarraySum(vector<int>& nums, int k) {
    unordered_map <int, int> sum2iMap = {{0, -1}};
    
    long long sum = 0;
    for (int i = 0; i < nums.size(); i++) {
      sum += nums[i];
      if (k)
        sum = sum %k;
      if (sum2iMap.count(sum) == 0) {
        sum2iMap[sum] = i;
        continue;
      } 
      if (i - sum2iMap[sum] > 1)
        return true;
    }
    return false;
  }

};

void printVec (vector <int> &v) {
  cout << "array: ";
  for (auto i: v) 
    cout << i << ' ';
  cout << '\n';
}

int main (void) {

  Solution sol;
  vector <int> vec {23,2,6,4,7};
  bool ret = sol.checkSubarraySum(vec, 6);
  printVec(vec);

  cout << "checkSubArray returned " << boolalpha << ret << '\n';

  return 0;
}
