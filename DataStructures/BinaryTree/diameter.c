
#include <stdio.h>
#include <stdlib.h>
 
struct node {
    int data;
    struct node* left;
    struct node* right;
};

static int max (int a, int b) {
  return (a >= b)? a: b;
}  

// This is height counting up from the leaf
int height (struct node* node) {
   if (node == NULL)
       return 0;

   return 1 + max(height(node->left), height(node->right));
}
 
struct node* newNode (int data) {
    struct node* node = calloc(1, sizeof(*node));
    if (node) node->data = data;
    return node;
}

/* Function to get diameter of a binary tree. 
 * It's longest path between two leaves.
 * In some cases, it's possible that diameter does not go through ROOT.
 * Especially if the tree is one sided. Imagine only one node on right.
 * and arbitrarily complex structure on left.
*/
int diameter (struct node * tree)
{
   /* base case where tree is empty */
   if (tree == 0)
     return 0;
 
  /* get the height of left and right sub-trees */
  int lheight = height(tree->left);
  int rheight = height(tree->right);
 
  printf("height L:%d R:%d total:%d\n", 
         lheight, rheight, lheight + rheight +1);
  
  /* get the diameter of left and right sub-trees */
  int ldiameter = diameter(tree->left);
  int rdiameter = diameter(tree->right);
 
  printf("diameter L:%d R:%d\n", ldiameter, rdiameter);
  
  /* Return max of following three
   1) Diameter of left subtree
   2) Diameter of right subtree
   3) Height of left subtree + height of right subtree + 1 */
  return max(lheight + rheight, max(ldiameter, rdiameter));
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
 
  printf("Diameter of the given binary tree is %d\n", diameter(root));
 
  getchar();
  return 0;
}
