#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


/*
  Check if two nodes are cousins in a Binary Tree

  Given the binary Tree and the two nodes say ?a? and ?b?, determine whether
  the two nodes are cousins of each other or not.
  
  Two nodes are cousins of each other if they are at same level and have
  different parents.
  
Example

     6
   /   \
  13     5
 / \   / \
7   8 1   3

Say two node be 7 and 1, result is TRUE.
Say two nodes are 13 and 5, result is FALSE.
Say two nodes are 7 and 5, result is FALSE.

*/

typedef struct node_ node_t;

struct node_ {
    struct node_ *left, *right;
    int key;
};


static bool
is_sibling (node_t *root, node_t *a, node_t *b) {
    if (!root) 
        return false;

    if ((root->left == a) && (root->right == b)) {
        return true;
    }
    if ((root->left == b) && (root->right == a)) {
        return true;
    }
    return is_sibling(root->left, a, b) || is_sibling(root->right, a, b);
}

unsigned get_level (node_t *root, node_t *a, int level) {
    if (root  == NULL) 
        return 0;
    if (root == a) {
        return level;
    }

    int left_level = get_level(root->left, a, level + 1);
    if (left_level != 0) 
        return left_level;
    return get_level(root->right, a, level + 1);
}

static bool 
levels_equal (node_t *root, node_t *a, node_t *b) {
    if (!root || !a || !b) return false;
    return get_level(root, a, 0) == get_level(root, b, 0);
}
     
static bool 
is_cousin (node_t *root, node_t *a, node_t *b) {

    // is_cousin if level is same and parent is not same.
    if (is_sibling(root, a, b)) {
        /* is_sibling means parents are same => not a cousin.
         */
        return false;
    }

    return levels_equal(root, a, b);
}

static node_t *newNode (int key) {
    node_t *n = calloc(1, sizeof *n);
    if (n) n->key = key;
    return n;
}

int main () {

  /* Constructed binary tree is
            4
          /   \
       12      5
      /  \      \
    1     3      10
  */
  struct node_ *root = newNode(4);
  root->left        = newNode(12);
  root->right       = newNode(5);
  root->left->left  = newNode(1);
  root->left->right = newNode(3);
  root->right->right = newNode(10);
  bool ret = is_cousin(root, root->left->left, root->right->right);

  printf("is_cousin() ret: %s\n", ret ? "true" : "false");

  return 0;

}
