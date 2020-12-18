/*

Given a binary tree, return the vertical order traversal of its nodes values.

For each node at position (X, Y), its left and right children respectively will
be at positions (X-1, Y-1) and (X+1, Y-1).

Running a vertical line from X = -infinity to X = +infinity, whenever the
vertical line touches some nodes, we report the values of the nodes in order
from top to bottom (decreasing Y coordinates).

If two nodes have the same position, then the value of the node that is reported
first is the value that is smaller.

Return an list of non-empty reports in order of X coordinate. Every report will
have a list of values of nodes.

Example 1:

Input: [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Explanation: 
Without loss of generality, we can assume the root node is at position (0, 0):
Then, the node with value 9 occurs at position (-1, -1);
The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
The node with value 20 occurs at position (1, -1);
The node with value 7 occurs at position (2, -2).

Example 2:

Input: [1,2,3,4,5,6,7]
Output: [[4],[2],[1,5,6],[3],[7]]
Explanation: 
The node with value 5 and the node with value 6 have the same position according to the given scheme.
However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.

Note:

    The tree will have between 1 and 1000 nodes.
    Each node's value will be between 0 and 1000.

*/

#include <map>
#include <set>
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
  // sort based on <row, col, val>
  map <int, set <pair<int,int>> > mp; // x --> { y, value } lower x first, lower y first, lower val first

  // why map ? Because map is an ordered data structure. The order is according
  // to the key, which here is tree level. lower key first.

  // why set ? Because set is an ordered data structure. If two nodes have the
  // same position, then the value of the node that is reported first is the
  // value that is smaller. 
  // set <pair <a, b>> // orders on lower a first, if a is same, then orders on lower b first.
  
  // vertical order is row wise ordering, row = level
  void pre ( TreeNode *root, int x, int y ){
    if(!root)
      return ;
    mp[x].insert( {y, root->val} );
    pre(root->left, x-1, y+1);
    pre(root->right, x+1, y+1);
  }
  
public:
  vector<vector<int>> verticalTraversal(TreeNode* root) {
    pre(root, 0, 0 );
    vector <vector<int>> v;
    for (auto [x, s] : mp ) {
      vector<int> c;

      for (auto [y, val] : s )
        c.push_back(val);

      v.push_back(c);
    }
    return v;
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
  vector <vector <int>> res = sol.verticalTraversal(root);
  print_vec_vec(res);

  return 0;
}
