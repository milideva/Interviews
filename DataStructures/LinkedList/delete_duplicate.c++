#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

/* 
82. Remove Duplicates from Sorted List II


Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list sorted as well.

 

Example 1:


Input: head = [1,2,3,3,4,4,5]
Output: [1,2,5]
Example 2:


Input: head = [1,1,1,2,3]
Output: [2,3]
 

Constraints:

The number of nodes in the list is in the range [0, 300].
-100 <= Node.val <= 100
The list is guaranteed to be sorted in ascending order.

*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return head;
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        ListNode *prev = dummy, *curr = head;
        ListNode *del = nullptr;
        while (curr) {
            if (curr->next && curr->val == curr->next->val) {
                while (curr->next && curr->val == curr->next->val) {
                    del = curr;
                    curr = curr->next;
                    delete del;
                }
                prev->next = curr->next;
                del = curr;
                curr = curr->next;
                delete del;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        return dummy->next;
    }
};

// Utility function to create a linked list from a vector
ListNode* createLinkedList(vector<int> vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* current = head;
    for (int i = 1; i < vals.size(); ++i) {
        current->next = new ListNode(vals[i]);
        current = current->next;
    }
    return head;
}

// Utility function to convert a linked list to a vector
vector<int> linkedListToVector(ListNode* head) {
    vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// Utility function to delete a linked list to free memory
void deleteLinkedList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void testDeleteDuplicates() {
    Solution sol;

    // Test case 1: [1,2,3,3,4,4,5] -> [1,2,5]
    ListNode* head1 = createLinkedList({1,2,3,3,4,4,5});
    ListNode* result1 = sol.deleteDuplicates(head1);
    vector<int> expected1 = {1,2,5};
    assert(linkedListToVector(result1) == expected1);
    deleteLinkedList(result1);

    // Test case 2: [1,1,1,2,3] -> [2,3]
    ListNode* head2 = createLinkedList({1,1,1,2,3});
    ListNode* result2 = sol.deleteDuplicates(head2);
    vector<int> expected2 = {2,3};
    assert(linkedListToVector(result2) == expected2);
    deleteLinkedList(result2);

    // Additional Test case 3: [1,1,2,3,3] -> [2]
    ListNode* head3 = createLinkedList({1,1,2,3,3});
    ListNode* result3 = sol.deleteDuplicates(head3);
    vector<int> expected3 = {2};
    assert(linkedListToVector(result3) == expected3);
    deleteLinkedList(result3);

    // Additional Test case 4: [1,1,1,1,1] -> []
    ListNode* head4 = createLinkedList({1,1,1,1,1});
    ListNode* result4 = sol.deleteDuplicates(head4);
    vector<int> expected4 = {};
    assert(linkedListToVector(result4) == expected4);
    deleteLinkedList(result4);

    // Additional Test case 5: [1,2,2,3,4,4,5,5] -> [1,3]
    ListNode* head5 = createLinkedList({1,2,2,3,4,4,5,5});
    ListNode* result5 = sol.deleteDuplicates(head5);
    vector<int> expected5 = {1,3};
    assert(linkedListToVector(result5) == expected5);
    deleteLinkedList(result5);

    cout << "All test cases passed!" << endl;
}

int main() {
    testDeleteDuplicates();
    return 0;
}
