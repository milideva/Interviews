
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

static void process_node (struct node *node) {
    printf("%d ", node->data);
}

void inOrder (struct node *node) {
    if (!node) return;
    inOrder(node->left);
    process_node(node);
    inOrder(node->right);
}

/* Height is the longest path from root to a leaf */
int height (struct node *node) {
    if (!node) return 0;
    int lHeight = height(node->left);
    int rHeight = height(node->right);
    int maxHeight = lHeight > rHeight ? lHeight : rHeight;
    return 1 + maxHeight;
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
  
  printf("tree inOrder : ");
  inOrder(root);

  printf("\nHeight of the tree is : %d \n", height(root));

  getchar();
  return 0;
}
