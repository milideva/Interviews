#include <iostream>
#include <queue>

using namespace std;

/*
226. Invert Binary Tree
Given the root of a binary tree, invert the tree, and return its root.

Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]

Input: root = [2,1,3]
Output: [2,3,1]

Example 

Before invert :
       6
     /   \
   13     5
  / \    / \
 7   8  1   3

After invert : 
       6
     /   \
    5     13
   / \   /  \
  3   1 8    7

*/
struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode *next;
  TreeNode() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

#define MY_NULL (-999)

class Solution
{

public:
  TreeNode *invertTree(TreeNode *root)
  {
    if (!root)
      return nullptr;
    TreeNode *left = invertTree(root->left);
    TreeNode *right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
  }
};

static void inorder(TreeNode *root)
{
  if (root)
  {
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
  }
}

void printTreeInorder(TreeNode *n)
{
  cout << "Inorder:" << endl;
  inorder(n);
  cout << endl;
}

static void postorder(TreeNode *root)
{
  if (root)
  {
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
  }
}

void printTreePostorder(TreeNode *n)
{
  cout << "Postorder:" << endl;
  postorder(n);
  cout << endl;
}

void print_vec_vec(vector<vector<int>> &res, string str)
{
  cout << endl << str << endl;
  for (auto v : res)
  {
    for (auto e : v)
    {
      cout << e << " ";
    }
    cout << endl;
  }
}

void print_vec(vector<int> &res, string str)
{
  cout << endl << str << endl;
  for (auto v : res)
  {
    cout << v << " ";
  }
  cout << endl;
}

// Helper function to create a BST
TreeNode *create_BST_from_array(int array[], int start, int end)
{
  if (!array)
    return NULL;
  if (start > end)
    return NULL;

  int mid = (start + end) / 2;
  if (array[mid] == MY_NULL)
  {
    return NULL;
  }
  TreeNode *n = new TreeNode(array[mid]);
  if (!n)
    return n;

  n->left = create_BST_from_array(array, start, mid - 1);
  n->right = create_BST_from_array(array, mid + 1, end);

  printf("TreeNode:%d left:%d right:%d\n", n->val,
         n->left ? n->left->val : -999,
         n->right ? n->right->val : -999);
  return n;
}

int main()
{

  int array[] = {1, 2, 3, 4, 5, 6, 7};
  int sz = sizeof array / sizeof array[0];
  TreeNode *root = create_BST_from_array(array, 0, sz - 1);

  printTreeInorder(root);
  printTreePostorder(root);

  class Solution sol;
  root = sol.invertTree(root);

  printTreeInorder(root);
  printTreePostorder(root);

  return 0;
}
