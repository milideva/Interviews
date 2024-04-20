/*

Given a non-empty binary search tree and a target value, find the value in the
BST that is closest to the target.

Note: Given target value is a floating point. You are guaranteed to have only
one unique value in the BST that is closest to the target.

Example:

Input: root = [4,2,5,1,3], target = 3.714286

Output: 4

*/



#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <iomanip>

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
  
  vector <int> inOrder;
  
  void getInOrder (TreeNode* root) {
    if (!root)
      return;
    getInOrder(root->left);
    inOrder.push_back(root->val);
    getInOrder(root->right);
  }
    
public:
  int closestValueOn(TreeNode* root, double target) {
    getInOrder(root);
    double bestDiff = DBL_MAX;
    int bestVal = INT_MAX;
    for (int i = 0; i < inOrder.size(); i++) {
      double diff = abs(inOrder[i] - target);
      if (diff < bestDiff) {
        bestDiff = diff;
        bestVal = inOrder[i];
        continue;
      }
      if (diff > bestDiff) {
        break;
      }
    }
    return bestVal;
  }

  // Recursive
  int closestValue(TreeNode* root, double target) {
    // If target < root->val, search the left subtree.
    if (target < root->val && root->left) {
      const int left = closestValue(root->left, target);
      if (abs(left - target) < abs(root->val - target))
        return left;
    }

    // If target > root->val, search the right subtree.
    if (target > root->val && root->right) {
      const int right = closestValue(root->right, target);
      if (abs(right - target) < abs(root->val - target))
        return right;
    }

    return root->val;
  }
  
  // Iterative
  int closestValue(TreeNode* root, double target) {
    double bestDiff = DBL_MAX;
    int bestVal = INT_MAX;
    
    while (root) {
      if (abs(root->val - target) < bestDiff) {
        bestDiff = abs(root->val - target);
        bestVal = root->val;
      }
      if (target < root->val)
        root = root->left;
      else 
        root = root->right;
    }
    
    return bestVal;
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
    int array[] = { -10, 5, 10, 56, 60, 100, 233, 300, 500, 600, 700, 800, 900, 1000, 2333 };
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
  double target = 850.00001;
  
  cout << std::setprecision(5) << std::fixed;

  int res = sol.closestValue(root, target);
  cout << "Target: " << target << " Closest value:" << res << '\n';

  target = 849.99999;
  res = sol.closestValue(root, target);
  cout << "Target: " << target << " Closest value:" << res << '\n';

  return 0;
}
