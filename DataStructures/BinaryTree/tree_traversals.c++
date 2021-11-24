
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

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

  void preOrderTraversalHelper(TreeNode* root, vector<int> &vec) {
    if (!root)
      return;
    vec.push_back(root->val);
    preOrderTraversalHelper(root->left, vec);
    preOrderTraversalHelper(root->right, vec);
  }

  bool isSymmetricHelper(TreeNode* l, TreeNode* r) {
        if (!l && !r) return true;
        if (!l && r) return false;
        if (l && !r) return false;
        if (l->val != r->val) return false;
        return isSymmetricHelper(l->left, r->right) && isSymmetricHelper(l->right, r->left);
    }
    
public:

  vector<int> preOrderTraversal(TreeNode* root) {
    vector <int> vec;
    if (!root) return vec;
    preOrderTraversalHelper(root, vec); 
    return vec;
  }

  vector <int> preOrderIterative (TreeNode* root) {
    vector <int> ans;
    if (!root)
      return ans;
    stack <TreeNode *> stk;
    stk.push(root);
    while (!stk.empty()) {
      auto rt = stk.top();
      stk.pop();
      ans.push_back(rt->val);
      if (rt->right) {
	stk.push(rt->right);
      }
      if (rt->left) {
	stk.push(rt->left);
      }
    }
    return ans;
  }

  vector<vector<int>> levelOrder(TreeNode* root) {
        vector <vector <int>> answer;
        if (!root) 
            return answer;
        queue <TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector <int> levelVec;

            while (size--) {
                TreeNode* node = q.front();
                q.pop();
                levelVec.push_back(node->val);
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }

            answer.push_back(levelVec);
            
        }
        return answer;
    }

    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isSymmetricHelper(root->left, root->right);
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

  int array[] = { -10, 5, 10, 56, 60, 100, 233, 300, 500, 600, 700, 800, 900, 1000, 2333 };
  int sz = sizeof array / sizeof array[0];
  TreeNode *root = create_tree(array, sz);
  
  vector <int> res = sol.preOrderTraversal(root);
  print_vec(res, "preOrder");
  res.clear();
  res = sol.preOrderIterative(root);
  print_vec(res, "preOrderIterative");

  vector <vector<int>> ans = sol.levelOrder(root);
  print_vec_vec(ans, "levelOrder");

  //int arr[] = {1,2,2,0,3,0,3};
  int arr[] = {MY_NULL, 2, 3, 1, MY_NULL, 2, 3};
  
  sz = sizeof arr / sizeof arr[0];
  root = create_tree(arr, sz-1);
  bool isMirror = sol.isSymmetric(root);
  cout << endl << (isMirror ? "symmetric" : "not symmetric") << endl;

  //int arr2[] = {1,2,2,3,4,4,3};
  int arr2[] = {3, 2, 4, 1, 4, 2, 3};
  sz = sizeof arr2 / sizeof arr2[0];
  root = create_tree(arr2, sz-1);
  isMirror = sol.isSymmetric(root);
  cout << endl << (isMirror ? "symmetric" : "not symmetric") << endl;

  return 0;
}
