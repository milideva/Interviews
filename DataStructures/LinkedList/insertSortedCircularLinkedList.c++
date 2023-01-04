#include <iostream>

using namespace std;

/*

  708. Insert into a Sorted Circular Linked List

  Given a node from a Circular Linked List which is sorted in ascending order,
  write a function to insert a value insertVal into the list such that it
  remains a sorted circular list. The given node can be a reference to any
  single node in the list, and may not be necessarily the smallest value in the
  circular list.

  If there are multiple suitable places for insertion, you may choose any place
  to insert the new value. After the insertion, the circular list should remain
  sorted.
  
  If the list is empty (i.e., given node is null), you should create a new
  single circular list and return the reference to that single node. Otherwise,
  you should return the original given node.

Example 1:
 
Input: head = [3,4,1], insertVal = 2
Output: [3,4,1,2]

Explanation: In the figure above, there is a sorted circular list of three
elements. You are given a reference to the node with value 3, and we need to
insert 2 into the list. The new node should be inserted between node 1 and node
3. After the insertion, the list should look like this, and we should still
return node 3.



Example 2:

Input: head = [], insertVal = 1
Output: [1]

Explanation: The list is empty (given head is null). We create a new single
circular list and return the reference to that single node.

Example 3:

Input: head = [1], insertVal = 0
Output: [1,0]

*/

class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

Node *createNode (int val) {
  Node *n = new Node{val};
  return n;
}

Node *createLL (void) {
  Node *head = new Node{20, nullptr};
  head->next = new Node{40, nullptr};
  head->next->next = new Node{60, nullptr};
  head->next->next->next = new Node{80, nullptr};
  head->next->next->next->next = new Node{100, nullptr};
  head->next->next->next->next->next = head;
  return head;
}

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node *n = new Node{insertVal};
        if (!head) {
            n->next = n;
            return n;
        }
        if (head->next == head) {
            head->next = n;
            n->next = head;
            return head->val < n->val ? head : n;
        }
        Node *prev = head;
        Node *curr = head->next;
        do {
            if (prev->val <= insertVal && insertVal <= curr->val) {
                // Case 1 regular easy case
                prev->next = n;
                n->next = curr;
                return head;
            }
            if (curr->val < prev->val) {
                // Case 2 between max and min of circular list - detect tail
                if (insertVal >= prev->val || insertVal <= curr->val) {
                    prev->next = n;
                    n->next = curr;
                    return head;
                }
            }
            prev = curr;
            curr = curr->next;
            
        } while (prev != head);
        // Case 3 : list contains uniform values.
        prev->next = n;
        n->next = curr;
        return head;
    }
};

void print (Node *head) {
  Node *curr = head;
  cout << "List: " ;
  while (curr->next != head) {
    cout << curr->val << " ";
    curr = curr->next;
  }
  cout << curr->val << endl;
}

int main (void) {
  Node *head = createLL();
  print(head);

  Solution sol;
  Node *hd1 = sol.insert(head, 10);
  print(hd1);

  hd1 = sol.insert(head, 40);
  print(hd1);

  hd1 = sol.insert(head, 110);
  print(hd1);

  return 0;
}
