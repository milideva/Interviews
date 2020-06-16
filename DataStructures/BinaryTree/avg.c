#include <stdio.h>
#include <stdlib.h>

/* This is not scalable way of solving this, better solve using BFS */
/* See avg_bfs.c */

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};
 
unsigned getTreeHeight (struct TreeNode* root) {
    if (!root) return 0;
    unsigned leftH = getTreeHeight(root->left);
    unsigned rightH = getTreeHeight(root->right);
    if (leftH > rightH) return leftH + 1;
    return rightH + 1;
}

// 0 based
int getMyHeight (struct TreeNode* root, struct TreeNode *node, int level) {
    if (!root || !node) return 0;
    if (root == node) return level;
    int myLevel  = getMyHeight(root->left, node, level+1);
    if (myLevel != 0) 
        return myLevel;
    return getMyHeight(root->right, node, level + 1);
}

void getAvg (struct TreeNode* root, struct TreeNode* node, int level, int *sum, int *numNodes) {
    if (!root || !node) return;
    int height = 0;
    height = getMyHeight(root, node, height);
    
    if (height > level) 
        return;
    if (height < level) {
        getAvg(root, node->left, level, sum, numNodes);
        getAvg(root, node->right, level, sum, numNodes);
        return;
    }
    *sum += node->val;
    *numNodes += 1;

    return;
}

double getAvgAtHeight (struct TreeNode* root, int level) {
    int sum = 0;
    int numNodes = 0;
    getAvg(root, root, level, &sum, &numNodes);
    printf("level:%d sum:%d numNodes:%d\n", level, sum, numNodes);
    double ret = (double)sum / (double)numNodes;
    return ret;
}

// Get average at each level of the tree, store in array of size tree height
double* averageOfLevels(struct TreeNode* root, int* returnSize){
    unsigned height = getTreeHeight(root);
    *returnSize = height;
    printf("getTreeHeight : %u\n", height);

    double *arr = calloc(height, sizeof(*arr));
    for (int level = 0; level < height; level++) {
        double avg = getAvgAtHeight(root, level);
        arr[level] = avg;
    }
    return arr;
}

struct TreeNode* newNode (int data) {
    struct TreeNode* node = calloc(1, sizeof(*node));
    if (node) node->val = data;
    return node;
}

int main() {

  /* Constructed binary tree is
            1
          /   \
        2      3
      /  \
    4     5
  */
  struct TreeNode *root = newNode(1);
  root->left        = newNode(2);
  root->right       = newNode(3);
  root->left->left  = newNode(4);
  root->left->right = newNode(5);

  int returnSize = 0;
  double *arr = NULL;
  arr = averageOfLevels(root, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    printf("Avg of the given binary tree at level [%d] is %f, size %d\n", i,
        arr[i], returnSize);
  }
  getchar();
  return 0;
}
