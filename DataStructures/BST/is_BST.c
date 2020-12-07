#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*
  The left subtree of a node contains only nodes with keys less than the
  node's key.  The right subtree of a node contains only nodes with keys
  greater than the node's key.  The left and right subtree each must also be a
  binary search tree.  Each node can have up to two nodes.  There
  must be no duplicate nodes.  A unique path exists from the root to every
  other node.
*/

// Validate BST : two solutions exist
// 1. min max technique
// 2. in-order traversal technique

struct node_ {
    int key;
    struct node_ *left;
    struct node_ *right;
};

typedef struct node_ node;

/* 
              100
           50      150
       30    60       170
     10 40  55  75
*/

/* max in left subtree must be < this node, input is child if it exists */
int max (node *node) {
    if (!node) return INT_MIN;
    int lmax = max(node->left);
    int rmax = max(node->right);
    int max = node->key;
    if (lmax > max) 
        max = lmax;
    if (rmax > max)
        max = rmax;
    return max;
}

/* min in right subtree must be > this node, input is child if it exists */
int min (node *node) {
    if (!node) return INT_MAX;
    int lmin = min(node->left);
    int rmin = min(node->right);
    int min = node->key;
    if (lmin < min)
        min = lmin;
    if (rmin < min)
        min = rmin;
    return min;
}

// This is grossly inefficient
bool isBST (node *node) {
    if (!node) 
        return true;

    /* Check immediate nodes */
    if (node->left && node->left->key > node->key) return false;
    if (node->right && node->right->key < node->key) return false;

    /* Get the values of max Left subtree and min Right subtree */
    if (node->left)  {
        int maxL = max(node->left);
        /* max in left subtree must be < this node */
        if (maxL > node->key) return false;
    }

    if (node->right) {
        int minR = min(node->right);
        /* min in right subtree must be > this node */
        if (minR < node->key) return false;
    }

    /* Recurse */
    return isBST(node->left) && isBST(node->right);
}

node *createNode (int key) {
    node *node = calloc(1, sizeof *node);
    if (node) node->key = key;
    return node;
}


/* 
    Optimized version.
    Compares with INT_MIN and INT_MAX
    But those could be a valid node key.
*/
bool isBST_2 (node *node, int min, int max) {
    /* Empty tree is a BST */
    if (!node) return true;
    
    if (node->key < min || node->key > max) return false;
    
    return isBST_2(node->left, min, node->key) && 
        isBST_2(node->right, node->key, max);
}

/* To avoid INT_MIN INT_MAX, this is better solution */
bool isBST_3 (node *node, int *min, int *max) {
    if (!node) return true;
    
    if (min && node->key < *min) return false;
    if (max && node->key > *max) return false;

    return isBST_3(node->left, min, &node->key) && isBST_3(node->right, &node->key, max);
}

bool isBST_efficient (node *node) {
    //return isBST_2(node, INT_MIN, INT_MAX);
    return isBST_3(node, NULL, NULL);
}


// 2. in-order traversal technique
// One way is to copy BST into an array as inorder traversal and then compare array for inorder or not
// Array will add O(n) space and is just used to check prev value with current
// Below code uses a global to track prev and avoids using array. O(1) space solution

struct node_ *prev;

bool isBST_inorder (node *node) {

    if (!node) return true;

    // printf("DEBUG node:%d prev:%d left:%d right:%d\n",node->key, prev ? prev->key : -1, node->left ? node->left->key : -1, node->right? node->right->key : -1);

    if (!isBST_inorder(node->left)) return false;

    if (prev && node->key < prev->key) {
            printf("inorder fails here node:%d < prev:%d \n",node->key, prev->key); 
            return false;
    }
    prev = node;
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

    printf("\nShould fail \nisBST() : %d\n", isBST(node));
    printf("isBST_efficient : %d\n",isBST_efficient(node));
    printf("isBST_inorder() : %d\n", isBST_inorder(node));

    free(node->left->left->right);
    node->left->left->right = createNode(40); // back to 40 should pass.
    printf("\nisBST() : %d\n", isBST(node));
    printf("isBST_efficient : %d\n",isBST_efficient(node));

    prev = NULL; // must reset this global var before calling isBST_inorder()
    printf("isBST_inorder() : %d\n", isBST_inorder(node));

    node->left->right->left =  createNode(45); // 55 made to 45 should fail
    printf("\nshould fail \nisBST() : %d\n", isBST(node));
    printf("isBST_efficient : %d\n",isBST_efficient(node));

    prev = NULL; // must reset this global var before calling isBST_inorder()
    printf("isBST_inorder() : %d\n", isBST_inorder(node));
}
