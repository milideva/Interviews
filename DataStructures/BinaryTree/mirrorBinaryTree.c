
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

void inOrder (struct node *node) {
    if (!node) return;
    inOrder(node->left);
    printf("%d ", node->data);
    inOrder(node->right);
}

/* Use Post order notation. 
   Excellent for things like changing nodes or freeing them.
   */
void mirror (struct node * node) {
    if (!node) return;
    mirror(node->left);
    mirror(node->right);
    // now swap left and right
    struct node *temp = node->left;
    node->left = node->right;
    node->right =  temp;
    return;
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
 

  printf("\n Inorder traversal of the constructed tree is \n");
  inOrder(root);

  mirror(root);
 
  printf("\n Inorder traversal of the mirror tree is \n");
  inOrder(root);

  getchar();
  return 0;
}
