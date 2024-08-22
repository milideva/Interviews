/*

    92. Reverse Linked List II


Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.

 

Example 1:


Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
Example 2:

Input: head = [5], left = 1, right = 1
Output: [5]
 

Constraints:

The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n


*/

#include <vector>
#include <iostream>
#include <cassert>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || left >= right ) return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode *prev = &dummy;

        for (int i = 0; i < left - 1; i++) {
            prev = prev->next;
        }

        ListNode *curr = prev->next;

        for (int i = 0; i < right - left; i++) {
            ListNode *next = curr->next;
            curr->next = next->next;
            next->next = prev->next;
            prev->next = next;
        }

        return dummy.next;
    }
};

// Function to convert a vector to a linked list
ListNode* vectorToList(const std::vector<int>& vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* current = head;
    for (size_t i = 1; i < vals.size(); i++) {
        current->next = new ListNode(vals[i]);
        current = current->next;
    }
    return head;
}

// Function to convert a linked list to a vector
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// Function to delete a linked list
void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void test (void) {

    Solution sol;

    // Test case 1
    ListNode* head1 = vectorToList({1, 2, 3, 4, 5});
    ListNode* result1 = sol.reverseBetween(head1, 2, 4);
    std::vector<int> expected1 = {1, 4, 3, 2, 5};
    assert(listToVector(result1) == expected1);
    deleteList(result1);

    // Test case 2
    ListNode* head2 = vectorToList({5});
    ListNode* result2 = sol.reverseBetween(head2, 1, 1);
    std::vector<int> expected2 = {5};
    assert(listToVector(result2) == expected2);
    deleteList(result2);

    // Test case 3: Reversing the entire list
    ListNode* head3 = vectorToList({1, 2, 3, 4, 5});
    ListNode* result3 = sol.reverseBetween(head3, 1, 5);
    std::vector<int> expected3 = {5, 4, 3, 2, 1};
    assert(listToVector(result3) == expected3);
    deleteList(result3);

    // Test case 4: Reversing a single element in the middle
    ListNode* head4 = vectorToList({1, 2, 3, 4, 5});
    ListNode* result4 = sol.reverseBetween(head4, 3, 3);
    std::vector<int> expected4 = {1, 2, 3, 4, 5};
    assert(listToVector(result4) == expected4);
    deleteList(result4);

    // Test case 5: Reversing the first two elements
    ListNode* head5 = vectorToList({1, 2, 3, 4, 5});
    ListNode* result5 = sol.reverseBetween(head5, 1, 2);
    std::vector<int> expected5 = {2, 1, 3, 4, 5};
    assert(listToVector(result5) == expected5);
    deleteList(result5);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test();
    return 0;
}

