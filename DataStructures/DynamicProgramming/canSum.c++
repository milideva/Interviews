#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
  Is it possible to generate target sum using numbers in nums.
  You may use a number in nums as many times as needed.
  Assume all numbers are non negative
*/


class Solution {
  unordered_set <int> memoSet;

  public:
  bool canSum (vector <int>& nums, int targetSum) {

    if (targetSum == 0) return true;
    if (targetSum < 0) return false;

    if (memoSet.find(targetSum) != memoSet.end()) {
      return true;
    }

    for (int i = 0; i < nums.size(); i++) {
      int remainder = targetSum - nums[i];
      if (canSum(nums, remainder) == true) {
        memoSet.insert(remainder);
        return true;
      }
    }
    return false;
  }

  vector <int> result;

  bool howSum (vector <int>& nums, int targetSum) {

    if (targetSum == 0) {
      return true;
    }
    if (targetSum < 0) {
      return false;
    }
    
    if (memoSet.find(targetSum) != memoSet.end()) {
      return true;
    }

    for (int i = 0; i < nums.size(); i++) {
      int remainder = targetSum - nums[i];
      if (howSum(nums, remainder) == true) {
        cout << "targetSum:" << targetSum << " i:" << i << " num:" << nums[i] << '\n';
        memoSet.insert(remainder);
        result.push_back(nums[i]);
        return true;
      }
    }
    return false;
  }
  
  bool isPrefix (string pre, string str) {
    if (str.find(pre) == 0) { // pre found and starts at pos 0
      return true;
    }
    return false;
  }

  string chopPrefix (string pre, string str) {
    if (str.find(pre) == 0) {
      string ret = str.substr(pre.length(), str.length() - pre.length());
      return ret;
    }
    return pre;
  }


  // Brute force
  // m = target.length and n = wordBank.length , time complexity is O( n^m   * m ) 
  // branching factor of tree = n words, and for each word,  worst case height of tree is m => n^m
  // this whole thing is called m times (target is sliced off prefix)
  // space : O(m * m) : m calls, m size of new string after slice
  bool canConstruct (vector <string>& wordBank, string target) {
    if (target.length() == 0) 
      return true;

    for (auto word : wordBank) {
      if (isPrefix(word, target)) {
        string remainder = chopPrefix(word, target); // slice prefix off the target 
        if (canConstruct(wordBank, remainder)) {
          return true;
        }
      }
    }
    return false;
  }

  unordered_map <string, bool>  memoMap;

  // Memoized version
  // time complexity is O( n   * m^2 )
  // space complexity O(m * m)
  bool canConstructMemoized (vector <string>& wordBank, string target) {
    if (target.length() == 0) 
      return true;

    if (memoMap.find(target) != memoMap.end()) 
      return memoMap[target];

    for (auto word : wordBank) {
      if (isPrefix(word, target)) {
        string remainder = chopPrefix(word, target); // slice prefix off the target 
        if (canConstruct(wordBank, remainder)) {
          memoMap[target] = true;
          return true;
        }
      }
    }
    memoMap[target] = false;
    return false;
  }

  void printSum (void) {
    cout << "result: " ;
    for (auto i : result) {
      cout << i << ' ';
    }
    cout << '\n';
  }

};

void printVec (vector <int> &v) {
  cout << "array: ";
  for (auto i: v) 
    cout << i << ' ';
  cout << '\n';
}

int main (void) {
/*
  Solution sol;
  vector <int> arr{1555, 100, 15, 77, 54, 53, 67, 676, 788, 6676, 78678, 22, 30, 25, 40, 1, 24, 42, 244, 575, 64, 645, 644, 96}; 
  int target = 70;

  bool ret = sol.canSum(arr, target);
  printVec(arr);
  cout << "target:" << target << '\n' << "canSum:" << boolalpha << ret << '\n';

  Solution sol2;
  bool ret2 = sol2.howSum(arr, target);
  cout << "target:" << target << '\n' << "howSum:" << boolalpha << ret2 << '\n';
  sol2.printSum();
*/
  Solution sol3;
  vector <string> wordBank = {"ab", "abc", "cd", "ef", "abcd"};
  string targetString = "abcdef";

  bool ret3 = sol3.canConstructMemoized(wordBank, targetString);
  cout << "target:" << targetString << '\n' << "canConstructMemoized:" << boolalpha << ret3 << '\n';

  return 0;
}
