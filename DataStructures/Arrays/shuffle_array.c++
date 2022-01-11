#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*

384. Shuffle an Array

Given an integer array nums, design an algorithm to randomly shuffle
the array. All permutations of the array should be equally likely as a
result of the shuffling.

Implement the Solution class:

Solution(int[] nums) Initializes the object with the integer array nums.
int[] reset() Resets the array to its original configuration and returns it.
int[] shuffle() Returns a random shuffling of the array.
 
Example 1:

Input
["Solution", "shuffle", "reset", "shuffle"]
[[[1, 2, 3]], [], [], []]
Output
[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]

Explanation
Solution solution = new Solution([1, 2, 3]);
solution.shuffle();    // Shuffle the array [1,2,3] and return its result.
                       // Any permutation of [1,2,3] must be equally likely to be returned.
                       // Example: return [3, 1, 2]
solution.reset();      // Resets the array back to its original configuration [1,2,3]. Return [1, 2, 3]
solution.shuffle();    // Returns the random shuffling of array [1,2,3]. Example: return [1, 3, 2]
 

Constraints:

1 <= nums.length <= 200
-106 <= nums[i] <= 106
All the elements of nums are unique.
At most 5 * 104 calls in total will be made to reset and shuffle.~

*/

class Solution {
    vector <int> orig;
public:
    Solution(vector<int>& nums) : orig(nums) {       
    }
    
    vector<int> reset() {
        return orig;
    }

    vector<int> shuffle() {
        vector <int> copy = orig;
        vector <int> shuffled = vector <int>();
        
        for (auto i = size(orig); i > 0; i--) {
            auto index = rand() % i;
            shuffled.push_back(copy[index]);
            copy[index] = copy.back();
            copy.pop_back();
        }
        return shuffled;
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
  vector <int> orig {1, 2, 3, 4, 5, 6, 7};
  printVec(orig, "Original: ");
  class Solution sol(orig);
  
  auto vec = sol.shuffle();
  printVec(vec, "Shuffled: ");
  
  return 0;
}
