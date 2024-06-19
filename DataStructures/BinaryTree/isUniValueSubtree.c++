
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;


/*
 Given the root of a binary tree, return the number of uni-value
 subtrees. A uni-value subtree means all nodes of the subtree have the
 same value.
*/

#define MY_NULL (-999)

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
  int count = 0;
  bool isUnival (TreeNode* root) {
    if (!root) return true;
    if (!root->left && !root->right) {
      // all leaf are unival
      count++;
      return true;
    }
    bool isUni = true;
    if (root->left) {
      isUni = (root->val == root->left->val) && isUnival(root->left);
    }
    if (root->right) {
      isUni = isUni && (root->val == root->right->val) && isUnival(root->right);
    }
    if (!isUni) 
      return false;
    count++;
    return true;
  }
  
public:
  int countUnivalSubtrees(TreeNode* root) {
    if (!root) return 0;
    isUnival(root);
    return count;
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
    if (start > end) return NULL;

    int mid = (start+end)/2;
    if (array[mid] == MY_NULL) {
      return NULL;
    }
    TreeNode *n = create_TreeNode(array[mid]);
    if (!n) return n;

    n->left = create_BST_from_array(array, start, mid-1);
    n->right = create_BST_from_array(array, mid+1, end);

    printf("TreeNode:%d left:%d right:%d\n", n->val,
           n->left ? n->left->val : -999,
           n->right ? n->right->val : -999);
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

TreeNode *create_tree (int *array, int size) {
    TreeNode *root = create_BST_from_array(array, 0, size);
    print_inorder(root);
    return root;
}

void print_vec_vec (vector <vector <int>> &res, string str) {
  cout << endl << str << endl;
  for (auto v: res) {
    for (auto e : v) {
      cout << e << " ";
    }
    cout << endl;
  }
}

void print_vec (vector <int> &res, string str) {
  cout << endl << str << endl;
  for (auto v:res) {
    cout << v << " ";
  }
  cout << endl;
}
  
int main () {
  class Solution sol;

  int array[] = { 5,1,5,   5, MY_NULL, 5, 5};
  int sz = sizeof array / sizeof array[0];
  TreeNode *root = create_tree(array, sz-1);
  
  int countUni = sol.countUnivalSubtrees(root);
  cout << "countUniValueSubtree:" << countUni << endl;
  return 0;
}
