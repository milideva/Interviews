
#include <vector>
#include <list>
#include <iostream>
#include <unordered_set>

using namespace std;
 
/*


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
  TreeNode* lowestCommonAncestor (TreeNode* p, TreeNode * q) {
    unordered_set <TreeNode *> uset;
    if (!p || !q) return nullptr;
    uset.insert(p);
    uset.insert(q);
    
    while (p->parent) {
      if (uset.find(p->parent) != uset.end()) return p->parent;
      uset.insert(p->parent);
      p = p->parent;
    }
    while (q->parent) {
      if (uset.find(q->parent) != uset.end()) return q->parent;
      uset.insert(q->parent);
      q = q->parent;
    }
    return nullptr;
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

  TreeNode *lca = sol.lowestCommonAncestor(p, q);
  if (lca) {
    cout << "LCA of p:" << p->val << " and q:" << q->val << " is " << lca->val << endl;
  } else {
    cout << "LCA of p:" << p->val << " and q:" << q->val << " not found" << endl;
  }

  p = findNode(root, -10);
  q = findNode(root, 900);

  lca = sol.lowestCommonAncestor(p, q);
  if (lca) {
    cout << "LCA of p:" << p->val << " and q:" << q->val << " is " << lca->val << endl;
  } else {
    cout << "LCA of p:" << p->val << " and q:" << q->val << " not found" << endl;
  }

  return 0;
}

