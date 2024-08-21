/*

86. Partition List

Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

 

Example 1:


Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
Example 2:

Input: head = [2,1], x = 2
Output: [1,2]
 

Constraints:

The number of nodes in the list is in the range [0, 200].
-100 <= Node.val <= 100
-200 <= x <= 200

*/


/*

Approach: Two Pointer Technique with Dummy Nodes
The idea is to use two pointers (or references) to create two separate linked lists:

One for nodes with values less than x
Another for nodes with values greater than or equal to x
At the end, we can combine the two linked lists to get the desired result.

*/

#include <iostream>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Function to create a linked list from a vector of values
ListNode* createLinkedList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// Function to convert linked list to vector for easy comparison
std::vector<int> linkedListToVector(ListNode* head) {
    std::vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// Function to delete a linked list to prevent memory leaks
void deleteLinkedList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode less(0), more(0);
        ListNode *lessCurr = &less, *moreCurr = &more;
        ListNode *curr = head;

        while (curr) {
            if (curr->val < x) {
                lessCurr->next = curr;
                lessCurr = curr;
            } else {
                moreCurr->next = curr;
                moreCurr = curr;
            }
            curr = curr->next;
        }
        
        lessCurr->next = more.next;
        moreCurr->next = nullptr;

        return less.next;
    }
};

void test (void) {

    Solution solution;

    // Test case 1: General case with mixed values
    ListNode* head1 = createLinkedList({1, 4, 3, 2, 5, 2});
    int x1 = 3;
    ListNode* result1 = solution.partition(head1, x1);
    std::vector<int> expected1 = {1, 2, 2, 4, 3, 5};
    std::vector<int> output1 = linkedListToVector(result1);
    std::cout << (output1 == expected1 ? "Test 1 Passed" : "Test 1 Failed") << std::endl;
    deleteLinkedList(result1);

    // Test case 2: All elements less than x
    ListNode* head2 = createLinkedList({1, 2, 2});
    int x2 = 3;
    ListNode* result2 = solution.partition(head2, x2);
    std::vector<int> expected2 = {1, 2, 2};
    std::vector<int> output2 = linkedListToVector(result2);
    std::cout << (output2 == expected2 ? "Test 2 Passed" : "Test 2 Failed") << std::endl;
    deleteLinkedList(result2);

    // Test case 3: All elements greater than or equal to x
    ListNode* head3 = createLinkedList({4, 5, 6});
    int x3 = 3;
    ListNode* result3 = solution.partition(head3, x3);
    std::vector<int> expected3 = {4, 5, 6};
    std::vector<int> output3 = linkedListToVector(result3);
    std::cout << (output3 == expected3 ? "Test 3 Passed" : "Test 3 Failed") << std::endl;
    deleteLinkedList(result3);

    // Test case 4: Empty list
    ListNode* head4 = nullptr;
    int x4 = 3;
    ListNode* result4 = solution.partition(head4, x4);
    std::vector<int> expected4 = {};
    std::vector<int> output4 = linkedListToVector(result4);
    std::cout << (output4 == expected4 ? "Test 4 Passed" : "Test 4 Failed") << std::endl;

    // Test case 5: Single element list
    ListNode* head5 = createLinkedList({1});
    int x5 = 2;
    ListNode* result5 = solution.partition(head5, x5);
    std::vector<int> expected5 = {1};
    std::vector<int> output5 = linkedListToVector(result5);
    std::cout << (output5 == expected5 ? "Test 5 Passed" : "Test 5 Failed") << std::endl;
    deleteLinkedList(result5);

}

int main() {
    test();
    return 0;
}