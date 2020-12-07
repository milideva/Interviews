#include <stdio.h>
#include <stdlib.h>

/*
Given a list of unique integers nums, construct a BST from it (you need to
insert nodes one-by-one with the given order to get the BST) and find the
distance between two nodes node1 and node2. Distance is the number of edges
between two nodes. If any of the given nodes does not appear in the BST, return
-1.
*/

struct node_ {
    int key;
    struct node_ *left;
    struct node_ *right;
};

typedef struct node_ node_t;

int height_from_node (node_t *root, node_t *me) {
    if (!root || !me || root == me) return 0;

    if (me->key < root->key) 
        return 1 + height_from_node(root->left, me);
    return 1 + height_from_node(root->right, me);
}

node_t *lowest_common_ancestor (node_t *root, node_t *n1, node_t *n2) {
    if (!root || !n1 || !n2) return NULL;
    if (n1->key < root->key && n2->key < root->key) 
        lowest_common_ancestor(root->left, n1, n2);
    if (n1->key > root->key && n2->key > root->key)
        lowest_common_ancestor(root->right, n1, n2);
   return root; 
}

// input is sorted array
node_t *create_BST (int array[], int start, int end) {
    if (!array || start > end) return NULL;

    int mid = (start + end)/ 2;

    node_t *node = calloc(1, sizeof *node);
    if (!node) return NULL;

    node->key = array[mid];
    node->left = create_BST(array, start, mid-1);
    node->right = create_BST(array, mid+1, end);

    return node;
}

int distance (node_t *root, node_t *n1, node_t *n2) {
    if (!root || !n1 || !n2 || n1==n2) return 0;

    node_t *lca = lowest_common_ancestor(root, n1, n2);
    return height_from_node(lca, n1) + height_from_node(lca, n2);
}

node_t *find_node (node_t *root, int key) {
    if (!root) return NULL;
    if (root->key == key) return root;

    if (key < root->key) return find_node(root->left, key);
    return find_node(root->right, key);    
}

void pre_order (node_t *root) {
    if (!root) return;
    printf("%d ", root->key);
    pre_order(root->left);
    pre_order(root->right);
}

int main () {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};  
    int n = sizeof(arr) / sizeof(arr[0]);

    node_t *root = create_BST(arr, 0, n-1);
    printf("Preorder traversal of constructed BST:\n");
    pre_order(root);

    int key1 = 1;
    int key2 = 7;
    node_t *n1 = find_node(root, key1);
    node_t *n2 = find_node(root, key2);

    int d = distance(root, n1, n2);
    printf("\ndistance between %d and %d is %d \n", key1, key2, d);
    return 0;
}
