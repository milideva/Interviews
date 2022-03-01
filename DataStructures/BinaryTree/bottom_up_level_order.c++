#include <vector>
#include <queue>
#include <iostream>


// g++ -std=c++2a bottom_up_level_order.c++ -g

/*

Given a binary tree, return the bottom-up level order traversal of its nodes'
values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]

*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
};

using namespace std;

void print_vec(const std::vector<int>& vec) {
  cout << "[ ";
  for (auto x: vec) {
    cout << ' ' << x;
  }
  cout << " ]" << endl;
}

void print_vec_vec (vector<vector<int>>& vec) {
  cout << "[ " << endl;
  for (auto x: vec) {
    print_vec(x);
    cout << ' ' << endl;
  }
  cout << " ]" << endl;
}

// Use BFS 
vector<vector<int>> levelOrderBottomBfs (TreeNode* root) {
  vector<vector<int>> answerQQ;                
  if (!root) return answerQQ;
  
  queue <TreeNode *> q;
  q.push(root); // put root in queue
  int level = 0;

  while (!q.empty()) {
    int sz = q.size();
    vector <int> levelVec;
    while (sz--) {
      TreeNode *n = q.front(); q.pop();
      if (n->left) 
        q.push(n->left);
      if (n->right)
        q.push(n->right);
      levelVec.push_back(n->val);
    }
    level++;
    answerQQ.push_back(levelVec);
  }
  reverse(answerQQ.begin(), answerQQ.end());
  return answerQQ;
}

int main () {
  TreeNode *root = new TreeNode;
  // [3,9,20,null,null,15,7]
  root->val = 3;
  
  root->left = new TreeNode;
  root->left->val = 9;
  
  
  root->right = new TreeNode;
  root->right->val = 20;
  
  root->right->left = new TreeNode;
  root->right->left->val = 15;
  
  root->right->right = new TreeNode;
  root->right->right->val = 7;
	
  vector<vector<int>> ans;
  ans = levelOrderBottomBfs(root);
  print_vec_vec(ans);
  
  return 0;
}
