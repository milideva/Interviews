#include <iostream>
#include <stack>


using namespace std;

/*
  The left subtree of a node contains only nodes with keys less than the
  node's key.  The right subtree of a node contains only nodes with keys
  greater than the node's key.  The left and right subtree each must also be a
  binary search tree.  Each node can have up to two nodes.  There
  must be no duplicate nodes.  A unique path exists from the root to every
  other node.
*/
struct node_ {
    int key;
    struct node_ *left;
    struct node_ *right;
};

typedef struct node_ node;


node *createNode (int key) {
    node *node = new node_;

    if (node) node->key = key;

    return node;
}

/* 
              100
           50      150
       30    60       170
     10 40  55  75
*/

void print_inorder_without_recursion (node *root) {
    stack <node *> stk;
    if (!root) return;
    node *curr = root;

    while (curr || stk.empty() == false) {
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top();
        stk.pop();
        cout << curr->key << " ";
        curr = curr->right;
    }
    cout << endl;
}

struct node_ *gprev; // beware - global var, must be reset to NULL every time this function is called
bool isBST_inorder (node *node) {
    if (!node) return true;

    if (!isBST_inorder(node->left)) 
       return false;
    if (gprev && node->key < gprev->key) {
        // printf("Fails node:%d prev:%d \n",node->key, gprev->key); 
        return false;
    }
    gprev = node;
    return isBST_inorder(node->right);
}

/* 
              100
           50      150
       30    60   111   170
     10 40  55  75
*/
int main () {
    node *node = createNode(100);
    node->left = createNode(50);
    node->right = createNode(150);

    node->left->left = createNode(30);
    node->left->right = createNode(60);

    node->right->left = createNode(111);
    node->right->right = createNode(170);

    node->left->left->left =  createNode(10);
    node->left->left->right = createNode(140); // 40 made to 140 should fail
    
    node->left->right->left =  createNode(55);
    node->left->right->right = createNode(75);

    cout << "isBST_inorder " << isBST_inorder(node) << endl;

    node->left->left->right = createNode(40); // back to 40 should pass.

    gprev = NULL;
    cout << "isBST_inorder " << isBST_inorder(node) << endl;

    node->left->right->left =  createNode(45); // 55 made to 45 should fail

    gprev = NULL;
    cout << "isBST_inorder " << isBST_inorder(node) << endl;

    print_inorder_without_recursion(node);

    return 0;

}
