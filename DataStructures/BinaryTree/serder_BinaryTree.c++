
#include <vector>
#include <list>
#include <iostream>
using namespace std;
 
/*

Serialization is the process of converting a data structure or object into a
sequence of bits so that it can be stored in a file or memory buffer, or
transmitted across a network connection link to be reconstructed later in the
same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no
restriction on how your serialization/deserialization algorithm should work. You
just need to ensure that a binary tree can be serialized to a string and this
string can be deserialized to the original tree structure.

Example 1:

Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:

Input: root = []
Output: []

Example 3:

Input: root = [1]
Output: [1]

Example 4:

Input: root = [1,2]
Output: [1,2]

*/
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
  void helperSer (TreeNode* root, string &res) {
    if (!root) {
      res += "null,";
      return;
    }
    res += to_string(root->val) + ",";
    helperSer(root->left, res);
    helperSer(root->right, res);
  }
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    string ser = "";
    helperSer(root, ser);
    return ser;
  }
  
  TreeNode * helperDeser(list <string>& lStr) {
    if (lStr.front() == "null") {
      lStr.pop_front();
      return NULL;
    }
    TreeNode* root = new TreeNode(stoi(lStr.front()));
    lStr.pop_front();
    root->left = helperDeser(lStr);
    root->right = helperDeser(lStr);
    return root;
  }


  TreeNode* deserialize(string data) {
    list <string> lStr;
    string tmp = "";
    // remove delimiter ,
    for (int i = 0; i < data.size(); i++) {
      if (data[i] == ',') {
        lStr.push_back(tmp);
        tmp = "";
      } else {
        tmp +=  data[i];
      }
    }
    
    TreeNode *root = helperDeser(lStr);
    return root;
  }
};

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
    printf("print_inorder: ");
    inorder(n);
}

int main (void) {

    int array[] = { -10, 5, 10, 56, 60, 100, 233, 300, 500, 600, 700, 800, 900, 1000, 2333 };
    int end = sizeof array/ sizeof array[0];
    TreeNode *root = create_BST_from_array(array, 0, end-1);
    print_inorder(root);

    class Codec cdc;

    string ser = cdc.serialize(root);
    cout << "Serialied string: " << ser;

    TreeNode *deserRoot = cdc.deserialize(ser);
    
    print_inorder(deserRoot);

    return 0;
}

