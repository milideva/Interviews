
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;

struct node* newNode (int data) {
    struct node* node = calloc(1, sizeof(*node));
    if (node) node->data = data;
    return node;
}

static bool nodeExists (node *root, node *x) {
    if (!root || !x) return false;

    if (root->data == x->data) return true;
    return nodeExists(root->left, x) || nodeExists(root->right, x);
}

node *common_ancestor (node *root, node *n1, node *n2) {
    if (!root) return NULL;
    // if a key is ancestor of another, it becomes the lca
    if (root == n1 || root == n2) return root;
    node *left = common_ancestor(root->left, n1, n2);
    node *right = common_ancestor(root->right, n1, n2);

    if (left && right) return root;
    return left ? left : right; 
}

// Assume tree is not a BST (no particular order)
static node *commonAncestor (node *root, node *n1, node *n2) {
    // First check whether n1 and n2 both exist in the tree 
    if (nodeExists(root, n1) == false) return false;
    if (nodeExists(root, n2) == false) return false;

    // Check if n1 and n2 both exist in left subtree root->left
    bool inLeft1 = nodeExists(root->left, n1);
    bool inLeft2 = nodeExists(root->left, n2);
    if (inLeft1 && inLeft2) 
        return commonAncestor(root->left, n1, n2);
    // Likewise check in right subtree
    if (nodeExists(root->right, n1) && nodeExists(root->right, n2)) {
        return commonAncestor(root->right, n1, n2);
    }   

    // One on left and one on right side, common ancestor is current root
    return root;
} 

int main() {
 
  /* Constructed binary tree is
            4
          /   \
        2      5
      /  \
    1     3
  */
  struct node *root = newNode(4);
  root->left        = newNode(2);
  root->right       = newNode(5);
  root->left->left  = newNode(1);
  root->left->right = newNode(3);
  

  node *common = commonAncestor(root, root->left->right, root->right);
  printf("common of %d and %d is %d \n", root->left->right->data, root->right->data, common ? common->data : -1 ); 

  common = commonAncestor(root, root->left->left, root->left->right);
  printf("common of %d and %d is %d \n", root->left->left->data, root->left->right->data, common ? common->data : -1 );

  return 0;
}
