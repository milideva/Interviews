
#include <vector>
#include <list>
#include <iostream>
#include <unordered_set>

using namespace std;
 
/*

236. Lowest Common Ancestor of a Binary Tree

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes p and q as the lowest node in T that has both p and q
as descendants (where we allow a node to be a descendant of itself).”

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

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
  TreeNode(int x) : val(x), left(NULL), right(NULL), parent(nullptr) {}
};

class Solution {
  
public:
  TreeNode* lowestCommonAncestor (TreeNode *root, TreeNode* p, TreeNode * q) {
    if (!root) return nullptr;
    if (root == p || root == q) return root;

    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);

    if (left && right) return root;
    if (!left && !right) return nullptr;
    
    return left ? left : right;
  }
};


// Test code ######################################################################################
TreeNode *create_TreeNode (int data) {
    TreeNode *node = (TreeNode *) calloc(1, sizeof *node);
    if (node) node->val = data;
    return node;
}

// Helper function to create a BST
TreeNode *create_BST_from_array (int array[], int start, int end) {
    if (!array) return NULL;
    if (end < start) return NULL;

    int mid = (start+end)/2;
    TreeNode *n = create_TreeNode(array[mid]);
    if (!n) return n;

    n->left = create_BST_from_array(array, start, mid-1);
    n->right = create_BST_from_array(array, mid+1, end);
    if (n->left) 
      n->left->parent = n;
    if (n->right) 
      n->right->parent = n;

    printf("TreeNode:%d left:%d right:%d parent:%d\n", n->val,
           n->left ? n->left->val : 0,
           n->right ? n->right->val : 0,
           n->parent ? n->parent->val : 0);
    return n;
}

static void inorder (TreeNode *root)  { 
    if (root) { 
        inorder(root->left); 
        printf("%d parent:%D\n", root->val, root->parent ? root->parent->val : 0); 
        inorder(root->right); 
    } 
}

TreeNode *findNode (TreeNode *root, int val) {

  while (root) {
    if (root->val == val) return root;
    if (val < root->val)
      root = root->left;
    else
      root = root->right;
  }
  return nullptr;
}

void print_inorder (TreeNode *n) {
    printf("print_inorder: ");
    inorder(n);
}

int main (void) {


 /* Constructed binary tree is
             300
             /  \
            /    \
           /      \
          /        \
         56        800
        / \         /  \
       /   \       /    \
      /     \     600     1000
     5    100    /  \      / \
    / \     /\  500  700  /   \
   /   \   60 233      900   2333
 -10   10

  */

  int array[] = { -10, 5, 10, 56, 60, 100, 233, 300, 500, 600, 700, 800, 900, 1000, 2333 };
  int end = sizeof array/ sizeof array[0];
  
  TreeNode *root = create_BST_from_array(array, 0, end-1);
  print_inorder(root);  

  class Solution sol;
  
  TreeNode *p, *q;
  p = findNode(root, 10);
  q = findNode(root, 60);

  TreeNode *lca = sol.lowestCommonAncestor(root, p, q);
  if (lca) {
    cout << "LCA of p:" << p->val << " and q:" << q->val << " is " << lca->val << endl;
  } else {
    cout << "LCA of p:" << p->val << " and q:" << q->val << " not found" << endl;
  }

  p = findNode(root, -10);
  q = findNode(root, 900);

  lca = sol.lowestCommonAncestor(root, p, q);
  if (lca) {
    cout << "LCA of p:" << p->val << " and q:" << q->val << " is " << lca->val << endl;
  } else {
    cout << "LCA of p:" << p->val << " and q:" << q->val << " not found" << endl;
  }

  return 0;
}

