#include <iostream>

using namespace std;

struct node_ {
    node_ *left, * right;
    int key;
};

typedef struct node_ node_t;

/* 
              100
           50      150
       30    60       170
     10 40  55  75
*/

/*
    In a BST, successor is the smallest element in the right subtree if right exist.
    else it is the parent.
*/
node_ *getSuccessor (node_ *root, int key) {

    if (!root) return nullptr;

    if (root->key == key) {
        if (root->right == nullptr) {
            // No successor if target is the rightmost node
            return nullptr;
        }
        // If right subtree exists, find minimum node there (successor)
        node_ *curr = root->right;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }
    if (key < root->key) {
        // Potential successor can be the current root or the max in its left subtree
        node_ *candidate = getSuccessor(root->left, key);
        return candidate ? candidate : root;
    }
    // Successor lies in the right subtree
    return getSuccessor(root->right, key);
}

node_t *getPredecessor (node_t *root, int key) {
    if (!root) return nullptr;
    if (root->key == key) {
        if (root->left == nullptr) {
            // No predecessor if target is the leftmost node in this subtree
            return nullptr;
        }
        // If left subtree exists, find maximum node there (predecessor)
        node_t *curr = root->left;
        while (curr->right) {
            curr = curr->right;
        }
        return curr;
    }
    if (key < root->key) {
        // Predecessor lies in the left subtree
        return getPredecessor(root->left, key);
    }
    // Potential predecessor can be the current root or its right subtree
    node_t *candidate = getPredecessor(root->right, key);
    return candidate ? candidate : root;
}

// Function to create a new node
node_t* createNode(int key) {
  node_t* newNode = new node_t;
  newNode->key = key;
  newNode->left = newNode->right = nullptr;
  return newNode;
}

// Function to insert a node into the BST
node_t* insert(node_t* root, int key) {
  if (!root) {
    return createNode(key);
  }

  if (key < root->key) {
    root->left = insert(root->left, key);
  } else if (key > root->key) {
    root->right = insert(root->right, key);
  }

  // Duplicate keys are not allowed
  return root;
}

void test (node_t *root, int target_key, int succ, int pred) {

  node_t* successor = getSuccessor(root, target_key);

  if (successor) {
    std::cout << "Successor of " << target_key << " is " << successor->key << " expected: " << succ << std::endl;
  } else {
    std::cout << "No successor found for " << target_key << std::endl;
  }

  node_t* predecessor = getPredecessor(root, target_key);

  if (predecessor) {
    std::cout << "Predecessor of " << target_key << " is " << predecessor->key << " expected: " << pred << std::endl;
  } else {
    std::cout << "No predecessor found for " << target_key << std::endl;
  }

}

node_t *create_test_bst (void) {
  node_t* root = nullptr;

  // Create the BST
  root = insert(root, 100);
  root = insert(root, 50);
  root = insert(root, 150);
  root = insert(root, 30);
  root = insert(root, 60);
  root = insert(root, 170);
  root = insert(root, 10);
  root = insert(root, 40);
  root = insert(root, 55);
  root = insert(root, 75);    

  return root;
}

/* 
              100
           50      150
       30    60       170
     10 40  55  75
*/

int main() {
  node_t* root = create_test_bst();

  int target_key = 50;
  int succ = 55;
  int pred = 40;
  test(root, target_key, succ, pred);

  target_key = 40;
  succ = 50;
  pred = 30;
  test(root, target_key, succ, pred); 

  target_key = 75;
  succ = 100;
  pred = 60;
  test(root, target_key, succ, pred); 

  target_key = 150;
  succ = 170;
  pred = 100;
  test(root, target_key, succ, pred); 

  target_key = 170;
  succ = -1;
  pred = 150;
  test(root, target_key, succ, pred); 

  target_key = 55;
  succ = 60;
  pred = 50;
  test(root, target_key, succ, pred); 
  return 0;
}