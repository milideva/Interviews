
/*

272. Closest Binary Search Tree Value II

Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:

Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
Example:

Input: root = [4,2,5,1,3], target = 3.714286, and k = 2

    4
   / \
  2   5
 / \
1   3

Output: [4,3]
Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
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
  priority_queue < pair <double, int> > pq; // < diff, value > 
  
  void handleMap (TreeNode *root,  double target, int k) {
    double diff = abs(root->val - target);
    pq.push({diff, root->val});
    if (pq.size() > k) {
      pq.pop();
    }
  }
  
  void inOrder (TreeNode *root,  double target, int k) {
    if (!root) return;
    inOrder(root->left, target, k);
    handleMap(root, target, k);
    inOrder(root->right, target, k);
  }
  
public:
  vector<int> closestKValues(TreeNode* root, double target, int k) {
    
    if (!root || k <= 0) return {};
    cout << "target:" << target << " k:" << k << '\n';

    inOrder(root, target, k);
    
    vector <int> ans;
    while (!pq.empty()) {
      ans.push_back(pq.top().second);
      pq.pop();
    } 
    
    sort(ans.begin(), ans.end());
    return ans;
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
void print_vec (vector <int> &res) {
  cout << "Vector : " << endl;
  for (auto v: res) {
      cout << v << " ";
  }
  cout << endl;
}

int main () {
  class Solution sol;
  TreeNode *root = create_tree();
  double target = 350.00001;

  cout << std::setprecision(5) << std::fixed;
  int k = 4;
  vector <int> res = sol.closestKValues(root, target, 4);
  print_vec(res);

  target = 849.99999;
  res = sol.closestKValues(root, target, 5);
  print_vec(res);

  return 0;
}
