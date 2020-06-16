
#include <stdio.h>
#include <stdlib.h>
 
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

int leafcount (struct node * node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return (leafcount(node->left) + leafcount(node->right));
}
 
int main() {
 
  /* Constructed binary tree is
            1
          /   \
        2      3
      /  \
    4     5
  */
  struct node *root = newNode(1);
  root->left        = newNode(2);
  root->right       = newNode(3);
  root->left->left  = newNode(4);
  root->left->right = newNode(5);
 
  printf("Leafcount of the given binary tree is %d\n", leafcount(root));
 
  getchar();
  return 0;
}
