
#include <vector>
#include <iostream>

using namespace std;
 
/*

1644. Lowest Common Ancestor of a Binary Tree II

Given the root of a binary tree, return the lowest common ancestor (LCA) of two given nodes, p and q. 
If either node p or q does not exist in the tree, return null. All values of the nodes in the tree are unique.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes p and q as the lowest node in T that has both p and q
as descendants (where we allow a node to be a descendant of itself).”

***********   Constraint : one of the nodes may not be in the tree. *************

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

Example 3:
Input: root = [1,2], p = 1, q = 2
Output: 1

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Solution class containing the lowestCommonAncestor function.
class Solution {
private:
    TreeNode* lcaHelper(TreeNode* root, TreeNode* p, TreeNode* q, bool& foundP, bool& foundQ) {
        if (!root) return nullptr;

        TreeNode* left = lcaHelper(root->left, p, q, foundP, foundQ);
        TreeNode* right = lcaHelper(root->right, p, q, foundP, foundQ);

        if (root == p) {
            foundP = true;
            return root;
        }
        if (root == q) {
            foundQ = true;
            return root;
        }

        if (left && right) return root;
        return left ? left : right;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        bool foundP = false;
        bool foundQ = false;
        TreeNode* lca = lcaHelper(root, p, q, foundP, foundQ);
        if (foundP && foundQ) {
            return lca;
        }
        return nullptr;
    }
};

// Helper function to create a binary tree from a vector.
TreeNode* createTree(const std::vector<int>& values, int index = 0) {
    if (index >= values.size() || values[index] == -1) {
        return nullptr;
    }
    TreeNode* root = new TreeNode(values[index]);
    root->left = createTree(values, 2 * index + 1);
    root->right = createTree(values, 2 * index + 2);
    return root;
}

// Helper function to find a node by value.
TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    TreeNode* leftResult = findNode(root->left, val);
    if (leftResult) return leftResult;
    return findNode(root->right, val);
}

// Test case function.
void testLowestCommonAncestor(const std::vector<int>& treeValues, int pVal, int qVal, int expectedVal) {
    TreeNode* root = createTree(treeValues);
    TreeNode* p = findNode(root, pVal);
    TreeNode* q = findNode(root, qVal);
    Solution sol;
    TreeNode* lca = sol.lowestCommonAncestor(root, p, q);
    if (lca) {
        std::cout << "LCA of nodes " << pVal << " and " << qVal << " is: " << lca->val << std::endl;
        if (lca->val == expectedVal) {
            std::cout << "Test passed." << std::endl;
        } else {
            std::cout << "Test failed. Expected LCA: " << expectedVal << std::endl;
        }
    } else {
        std::cout << "LCA not found." << std::endl;
        if (expectedVal == -1) {
            std::cout << "Test passed." << std::endl;
        } else {
            std::cout << "Test failed. Expected LCA: " << expectedVal << std::endl;
        }
    }
}

int main() {
    // Example 1
    std::vector<int> tree1 = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};
    testLowestCommonAncestor(tree1, 5, 1, 3);

    // Example 2
    testLowestCommonAncestor(tree1, 5, 4, 5);

    // Example 3
    std::vector<int> tree2 = {1, 2};
    testLowestCommonAncestor(tree2, 1, 2, 1);

    // Additional Test Case: Node not in tree
    testLowestCommonAncestor(tree1, 5, 10, -1);

    return 0;
}
