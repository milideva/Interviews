#include <vector>
#include <iostream>

using namespace std;

/*
    129. Sum Root to Leaf Numbers

    You are given the root of a binary tree containing digits from 0 to 9 only.

    Each root-to-leaf path in the tree represents a number.

    For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
    Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer will fit in a 32-bit integer.

    A leaf node is a node with no children.
    Input: root = [1,2,3]
    Output: 25
    Explanation:
    The root-to-leaf path 1->2 represents the number 12.
    The root-to-leaf path 1->3 represents the number 13.
    Therefore, sum = 12 + 13 = 25.

    Input: root = [4,9,0,5,1]
    Output: 1026
    Explanation:
    The root-to-leaf path 4->9->5 represents the number 495.
    The root-to-leaf path 4->9->1 represents the number 491.
    The root-to-leaf path 4->0 represents the number 40.
    Therefore, sum = 495 + 491 + 40 = 1026.

*/

/*
    Lets say the tree is:
                4
              /   \
            9      0
                     \
                      1
    DFS(4, 0) runs DFS(9, 4) + DFS(0, 4).
    DFS(9, 4) adds 49 to total.
    DFS(0, 4) adds runs DFS(NULL, 40) + DFS(1, 40).
    DFS(NULL, 40) doesn't do anything.
    DFS(1, 40) adds 401 to total.
    In the total == 450.

    If current == NULL return.
    If current->left == NULL && current->right == NULL there are no children.
        We will then  total += current->val and total += num * 10
    Else, recurse DFS(current->left, num*10 + current->val) and DFS(current->right, num*10 + current->val).
*/

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
    int sum = 0;
    void preOrder(TreeNode *root, int num)
    {
        if (!root)
        {
            return;
        }
        if (!root->left && !root->right)
        {
            sum += root->val;
            sum += num * 10;
        }

        preOrder(root->left, num * 10 + root->val);
        preOrder(root->right, num * 10 + root->val);
    }

public:
    int sumNumbers(TreeNode *root)
    {
        if (!root)
            return 0;
        preOrder(root, 0);
        return sum;
    }
};

void test(TreeNode *root)
{
    Solution sol;
    auto sum = sol.sumNumbers(root);
    cout << "sum: " << sum << endl;
}

int main(void)
{
    TreeNode *n1 = new TreeNode(1);
    TreeNode *n0 = new TreeNode(0, nullptr, n1);
    TreeNode *n9 = new TreeNode(9);
    TreeNode *root = new TreeNode(4, n9, n0);

    test(root);
    return 0;
}