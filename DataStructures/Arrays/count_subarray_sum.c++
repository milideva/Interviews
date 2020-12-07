/*
Given an array of integers nums and an integer k, return the total number of continuous subarrays whose sum equals to k.

Example 1:
Input: nums = [1,1,1], k = 2
Output: 2

Example 2:
Input: nums = [1,2,3], k = 3
Output: 2

Constraints:
     1 <= nums.length <= 2 * 104
    -1000 <= nums[i] <= 1000
    -107 <= k <= 107
*/

#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

int subarraySum (vector<int>& nums, int k) {

  int len = nums.size();
  
  if (!len) return 0;
  if (len == 1) return nums[0] == k ? 1 : 0;
  
  int count = 0;
  
  /* Brute Force - TLE
     for (int i = 0; i < len; i++) {
     int sum = nums[i];
     if (sum == k) 
                count++;
                for (int j = i+1; j < len; j++) {
                sum += nums[j];
                if (sum == k)
                count++;
                }
                
        }
  */
        
  unordered_map <int, int> m;
  
  int currSum = 0;
  m[0]++; // This is the key
  
  for (int i = 0; i < len; i++) {
    currSum += nums[i];
    if (m[currSum -k]) 
      count = count + m[currSum -k];
    m[currSum]++;
  }
  
  return count;
}


int main () {

  vector <int> nums = {1,2,3};
  int k = 3;

  int count = subarraySum(nums, k);

  cout << "Count: " << count << endl;
  return 0;
}
