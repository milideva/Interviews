#include <iostream>
#include <queue>

using namespace std;

/*
366. Find Leaves of Binary Tree

Given the root of a binary tree, collect a tree's nodes as if you were doing this:

Collect all the leaf nodes.
Remove all the leaf nodes.
Repeat until the tree is empty.

Input: root = [1,2,3,4,5]
Output: [[4,5,3],[2],[1]]

       1
      / \
     2   3
    / \
   4   5

Explanation:
[[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers since per each level it does not matter the order \
on which elements are returned.
Example 2:

Input: root = [1]
Output: [[1]]


Constraints:

The number of nodes in the tree is in the range [1, 100].
-100 <= Node.val <= 100
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
  vector <vector <int>> ans;
  int getHeight (TreeNode *root) {
    if (!root) 
      return -1;
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    int h = max(lh, rh) + 1;
    if (size(ans) == h) {
      ans.push_back({});
    }
    ans[h].push_back(root->val);
    return h;
  }
public:
  vector<vector<int>> findLeaves(TreeNode* root) {
    getHeight(root);
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

  int array[] = { 1, 2, 3, 4, 5, 6, 7 };
  int sz = sizeof array / sizeof array[0];
  TreeNode *root = create_BST_from_array(array, 0, sz-1);

  printTreeInorder(root);
  printTreePostorder(root);
  
  class Solution sol;
  auto ans = sol.findLeaves(root);

  print_vec_vec(ans, "answer for findLeaves()");
  //printTreeInorder(root);
  //printTreePostorder(root);

  return 0;
}
