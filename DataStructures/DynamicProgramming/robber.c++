/*
You are a professional robber planning to rob houses along a street. Each house
has a certain amount of money stashed, the only constraint stopping you from
robbing each of them is that adjacent houses have security system connected and
it will automatically contact the police if two adjacent houses were broken
into on the same night.

Given a list of non-negative integers representing the amount of money of each
house, determine the maximum amount of money you can rob tonight without
alerting the police.

 

Example 1:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.

Example 2:

Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.

*/

#include <vector>
#include <iostream>

using namespace std;

/*
  only 1 element in the array f1 = a[0]  
  only 2 elements in the array f2 = max (a[0], a[1])
  3 elements in the array f3 = f2 Or f1+a[2]
  ...
*/
int getSum (vector<int>& nums, int index) {
  int f1, f2, f3;
  f1 = nums[0];
  f2 = max(nums[0], nums[1]);
  int i = 2;
  while (i < index) {
    f3 = max(f2, f1 + nums[i]);
    i++;
    f1 = f2;
    f2 = f3;
  }
  return f3;
}

int rob (vector<int>& nums) {
  if (nums.size() == 0) return 0;
  if (nums.size() == 1) return nums[0];
  if (nums.size() == 2) return max(nums[0], nums[1]);
  return getSum(nums, nums.size());
}

void rob_test (vector<int>& nums) {

  cout << "max rob sum : " << rob(nums) << endl;
}

/*  House Robber II All houses at this place are arranged in a circle. That
 means the first house is the neighbor of the last one. Meanwhile, adjacent
 houses have a security system connected, and it will automatically contact the
 police if two adjacent houses were broken into on the same night.

Example 1:

Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

Example 2:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 3:

Input: nums = [0]
Output: 0


*/

int getSum (vector<int>& nums, int start, int end) {
  int f1, f2, f3;
  f1 = nums[start];
  f2 = max(nums[start], nums[start+1]);
  int i = start+2;
  while (i <= end) {
    f3 = max(f2, f1 + nums[i]);
    i++;
    f1 = f2;
    f2 = f3;
  }
  return f3;
}


int robII(vector<int>& nums) {
  if (nums.size() == 0) return 0;
  if (nums.size() == 1) return nums[0];
  if (nums.size() == 2) return max(nums[0], nums[1]); // should not this be 0 since it's circular?
  int max0 = getSum(nums, 0, nums.size()-2);
  int max1 = getSum(nums, 1, nums.size()-1);
  return max(max0, max1);
}

void robII_test (vector<int>& nums) {

  cout << "max robII sum : " << robII(nums) << endl;
}

int main () {

  vector <int> v {2, 7, 9, 3, 1};
  rob_test(v);

  robII_test(v);

  return 0;
}

/*

The thief has found himself a new place for his thievery again. There is only
one entrance to this area, called the "root." Besides the root, each house has
one and only one parent house. After a tour, the smart thief realized that "all
houses in this place forms a binary tree". It will automatically contact the
police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting
the police.

Example 1:

Input: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \ 
     3   1

Output: 7 
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.

Example 2:

Input: [3,4,5,1,3,null,1]

     3
    / \
   4   5
  / \   \ 
 1   3   1

Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.

*/

 struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

// Each node has two choices - to Rob or Not Rob
// Think from leaf, leading up, in array we started thinking from arr[0], then arr[1] ...
// The key point here it to return both fRob and fNotRob
pair<int, int> robDFS(TreeNode* node){
  if( !node) 
    return make_pair(0,0);
  auto l = robDFS(node->left);
  auto r = robDFS(node->right);
  int fNotRob = l.second + r.second;
  int fRob = max(fNotRob, l.first + r.first + node->val);
  return make_pair(fNotRob, fRob);
}

int robIII(TreeNode* root) {
  return robDFS(root).second;
}
