/*

  938. Range Sum of BST

  Given the root node of a binary search tree, return the sum of values of all
  nodes with a value in the range [low, high].

  Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
  Output: 32

  Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
  Output: 23

*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  int rangeSumBST(TreeNode* root, int low, int high) {
    if (!root) return 0;
    if (root->val < low)
      return rangeSumBST(root->right, low, high);
    if (root->val > high)
      return rangeSumBST(root->left, low, high);
    return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
  }
};

///////////////////////////////// Test code ////////////////////////////////////////
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

    printf("TreeNode:%d left:%d right:%d\n", n->val,
           n->left ? n->left->val : 0,
           n->right ? n->right->val : 0);
    return n;
}

static void inorder (TreeNode *root)  { 
  if (root) { 
    inorder(root->left); 
    printf("%d \n", root->val); 
    inorder(root->right); 
  } 
}

void print_inorder (TreeNode *n) {
  printf("print_inorder: \n");
  inorder(n);
}

TreeNode *create_tree () {
  int array[] = { -10, 5, 10, 55, 60, 100, 233, 300, 500, 600, 700, 800, 900, 1000, 2333 };
  int end = sizeof array/ sizeof array[0];
  TreeNode *root = create_BST_from_array(array, 0, end-1);
  print_inorder(root);
  return root;
}

void print_vec_vec (vector <vector <int>> &res) {
  cout << "Vertical order : " << endl;
  for (auto v: res) {
    for (auto e : v) {
      cout << e << " ";
    }
    cout << endl;
  }
}

int main () {
  class Solution sol;
  TreeNode *root = create_tree();
  
  int min = 5;
  int max = 60;

  int res;

  res = sol.rangeSumBST(root, min, max);
  cout << "Min: " << min << " Max: " << max << " Sum:" << res << '\n';

  min = 60;
  max = 100;
  res = sol.rangeSumBST(root, min, max);
  cout << "Min: " << min << " Max: " << max << " Sum:" << res << '\n';

  return 0;
}
