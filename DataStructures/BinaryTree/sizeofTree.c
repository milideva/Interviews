
#include <stdio.h>
#include <stdlib.h>

// size of tree = # elements in tree
 
struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode (int data) {
    struct node* node = calloc(1, sizeof(*node));
    if (node) node->data = data;
    return node;
}

int size (struct node *node) {
    if (!node) return 0;
    return 1 + size(node->left) +  size(node->right);
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
  
  printf("Size of the tree is : %d \n", size(root));

  getchar();
  return 0;
}
