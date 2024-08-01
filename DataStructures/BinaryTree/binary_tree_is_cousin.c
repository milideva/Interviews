#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


/*
  Check if two nodes are cousins in a Binary Tree

  Given the binary Tree and the two nodes say a and b, determine whether
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

// Use BFS to process nodes level by level, which is ideal for this case
// as we want to compare level and parent
bool are_cousins(TreeNode* root, int a, int b) {
    if (root == NULL) return false;

    queue<pair<TreeNode*, TreeNode*>> q; // Pair of (node, parent)
    q.push({root, nullptr});

    while (!q.empty()) {
        int size = q.size();
        TreeNode* parentA = NULL;
        TreeNode* parentB = NULL;

        for (int i = 0; i < size; ++i) {
            pair<TreeNode*, TreeNode*> front = q.front();
            q.pop();

            TreeNode* node = front.first;
            TreeNode* parent = front.second;

            if (node->val == a) parentA = parent;
            if (node->val == b) parentB = parent;

            if (node->left) q.push({node->left, node});
            if (node->right) q.push({node->right, node});

            // Check if both nodes are found at the same level
            if (parentA && parentB) return parentA != parentB;
        }

        // If only one node is found at this level, they cannot be cousins
        if ((parentA && !parentB) || (!parentA && parentB)) return false;
    }

    return false; // If we exit the loop without finding both nodes
}

// C++ version

// Recursive function to find levels and parents of nodes a and b
static void findLevelsAndParents(node_t *root, node_t *target, int level, node_t *parent, int &level_target, node_t *&parent_target)
{
  if (!root)
  {
    return;
  }

  if (root == target)
  { // when the target node is found
    level_target = level;
    parent_target = parent; // we need to save parent
    return;                 // Early termination if target found
  }

  findLevelsAndParents(root->left, target, level + 1, root, level_target, parent_target);
  findLevelsAndParents(root->right, target, level + 1, root, level_target, parent_target);
}

static bool isCousin(node_t *root, node_t *a, node_t *b)
{
  if (!root || !a || !b)
  {
    return false;
  }

  int level_a = -1, level_b = -1; // level is the depth from root
  node_t *parent_a = nullptr;
  node_t *parent_b = nullptr;

  // Find levels and parents for both nodes a and b
  findLevelsAndParents(root, a, 0, nullptr, level_a, parent_a);
  findLevelsAndParents(root, b, 0, nullptr, level_b, parent_b);

  // Check if levels are equal and parents are different
  return level_a != -1 && level_b != -1 && level_a == level_b && parent_a != parent_b;
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
