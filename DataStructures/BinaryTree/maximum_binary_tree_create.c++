#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*

654. Maximum Binary Tree

A maximum tree is a tree where every node has a value greater than any other value in its subtree.

You are given an integer array nums with no duplicates. 
A maximum binary tree can be built recursively from nums using the following algorithm:

Create a root node whose value is the maximum value in nums.
Recursively build the left subtree on the subarray prefix to the left of the maximum value.
Recursively build the right subtree on the subarray suffix to the right of the maximum value.
Return the maximum binary tree built from nums.

Input: nums = [3,2,1,6,0,5]
Output: [6,3,5,null,2,0,null,null,1]
Explanation: The recursive calls are as follow:
- The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right suffix is [0,5].
    - The largest value in [3,2,1] is 3. Left prefix is [] and right suffix is [2,1].
        - Empty array, so no child.
        - The largest value in [2,1] is 2. Left prefix is [] and right suffix is [1].
            - Empty array, so no child.
            - Only one element, so child is a node with value 1.
    - The largest value in [0,5] is 5. Left prefix is [0] and right suffix is [].
        - Only one element, so child is a node with value 0.
        - Empty array, so no child.
    
*/
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
    
    TreeNode* recurseMaximumBinaryTree (vector<int>& nums, int start, int end) {
        if (start > end) 
            return nullptr;
        int max = nums[start];
        int max_index = start;
        for (int i = start; i <= end; i++) {
            if (nums[i] > max) {
                max_index= i;
                max = nums[i];
            }
        }
        TreeNode *root = new TreeNode(max);
        root->left = recurseMaximumBinaryTree(nums, start, max_index - 1);
        root->right = recurseMaximumBinaryTree(nums, max_index + 1, end);
        return root;
    }

public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return recurseMaximumBinaryTree(nums, 0, nums.size() - 1);
    }
};

void inOrderPrint (TreeNode *root) {
    if (!root) return;
    inOrderPrint(root->left);
    cout << root->val << " " << endl;
    inOrderPrint(root->right);
}
void test(void) {
    class Solution sol;
    vector <int> nums{3,2,1,6,0,5};
    TreeNode *root = sol.constructMaximumBinaryTree(nums);
    inOrderPrint(root);
}

int main () {
    test(); 
    return 0;
}