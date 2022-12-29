// priority_queue:: push/pop/top/size/empty these are the only ops on a PQ
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>

using namespace std;

/*
    23. Merge k Sorted Lists

    You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

    Merge all the linked-lists into one sorted linked-list and return it.


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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto compare = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> minHeap(compare);

        ListNode dummy(0);
        ListNode *curr;

        for (auto node : lists) {
            if (node)
                minHeap.push(node);
        }

        curr = &dummy;

        while (!minHeap.empty()) {
            ListNode *node = minHeap.top();
            minHeap.pop();
            if (node->next) {
                minHeap.push(node->next);
            }
            curr->next = node;
            curr = node;
        }
        return dummy.next;
    }
};

ListNode *createList (int start, int step, int numNodes) {
    int val = start;
    ListNode dummy(0);
    ListNode *curr = &dummy;
    while (numNodes--) {
        ListNode *node = new ListNode(val);
        curr->next = node;
        node->next = nullptr;
        curr = node;
        val += step;
    }
    return dummy.next;
}

void printList (ListNode *list) {
    while (list) {
           cout << list->val << " ";
           list = list->next;
    }
    cout << endl;
}

int main () {
    vector <ListNode *> lists;

    int start = 0, step = 5, numNodes = 10;
    ListNode *list;
    
    list = createList(start, step, numNodes);
    lists.push_back(list);
    printList(list);
    
    list = createList(start - 2, step, numNodes);
    lists.push_back(list);
    printList(list);
    
    list = createList(start - 1, step, numNodes);
    lists.push_back(list);
    printList(list);
    
    list = createList(start + 1, step, numNodes);
    lists.push_back(list);
    printList(list);
    
    class Solution sol;
    list = sol.mergeKLists(lists);
    printList(list);
    
    return 0;   
}