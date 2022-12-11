#include <iostream>
#include <queue>

using namespace std;

// Populate each next pointer to point to its next right node at same
// height. If there is no next right node, the next pointer should be
// set to NULL.


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
  TreeNode* connect(TreeNode* root) {
    // This is a Simple BFS
    queue <TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      int size = q.size();
      while (size--) {
	      TreeNode *n = q.front(); q.pop();
	      if (size == 0) {
	        n->next = nullptr;
	      } else {
	        n->next = q.front();
	      }
	      if (n->left)
	        q.push(n->left);
	      if (n->right)
	        q.push(n->right);
      }
    }
    return root;
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

int main () {

  int array[] = { 5,1,5,   5, MY_NULL, 5, 5};
  int sz = sizeof array / sizeof array[0];
  TreeNode *root = create_BST_from_array(array, 0, sz-1);
  
  class Solution sol;
  root = sol.connect(root);
  
  return 0;
}
