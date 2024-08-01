#include <iostream>
#include <queue>

using namespace std;

/*
1022. Sum of Root To Leaf Binary Numbers

You are given the root of a binary tree where each node has a value 0
or 1. Each root-to-leaf path represents a binary number starting with
the most significant bit.

For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could
represent 01101 in binary, which is 13.  For all leaves in the tree,
consider the numbers represented by the path from the root to that
leaf. Return the sum of these numbers.

The test cases are generated so that the answer fits in a 32-bits
integer.

*/


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode *next;
  TreeNode() : val(0), left(nullptr), right(nullptr), next(nullptr){}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}  
};

#define MY_NULL (-999)

class Solution {

public:

  void dfs (TreeNode *node, int val, int& ans) {
    if (!node) return;
    val = (val * 2) + node->val;
    if (!node->left && !node->right) {
      ans += val;
      return;
    }
    dfs(node->left, val, ans);
    dfs(node->right, val, ans);
  }
  int sumRootToLeaf (TreeNode* root) {
    int ans = 0;
    dfs(root, 0, ans);
    return ans;
  }
};

static void inorder (TreeNode *root)  {
    if (root) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}


void printTreeInorder (TreeNode *n) {
  cout << "Inorder:" << endl;
  inorder(n);
  cout << endl;
}

static void postorder (TreeNode *root)  {
    if (root) {
        postorder(root->left);
	postorder(root->right);
        cout << root->val << " ";
    }
}


void printTreePostorder (TreeNode *n) {
  cout << "Postorder:" << endl;
  postorder(n);
  cout << endl;
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

// Helper function to create a BST
TreeNode *create_BST_from_array (int array[], int start, int end) {
    if (!array) return NULL;
    if (start > end) return NULL;

    int mid = (start+end)/2;
    if (array[mid] == MY_NULL) {
      return NULL;
    }
    TreeNode *n = new TreeNode(array[mid]);
    if (!n) return n;

    n->left = create_BST_from_array(array, start, mid-1);
    n->right = create_BST_from_array(array, mid+1, end);

    printf("TreeNode:%d left:%d right:%d\n", n->val,
           n->left ? n->left->val : -999,
           n->right ? n->right->val : -999);
    return n;
}

int main () {

  int array[] = { 1, 0, 1, 1, 1, 0, 1 };
  int sz = sizeof array / sizeof array[0];
  TreeNode *root = create_BST_from_array(array, 0, sz-1);

  printTreeInorder(root);
  printTreePostorder(root);
  
  class Solution sol;
  auto sum = sol.sumRootToLeaf(root);
  
  cout << "sum: " << sum << endl;
  return 0;
}
