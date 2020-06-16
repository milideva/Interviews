#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
 
/* Utility function to insert a node at the beginning */
void push (struct node **head, int new_data) {
    struct node *new_node = calloc(1, sizeof(*new_node));
    new_node->data = new_data;
    new_node->next = *head;
    *head = new_node;
}
 
void printList (struct node *node) {
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int getListSize (struct node *head) {
    int i = 0;
    while (head) {
        head = head->next;
        i++;
    }
    return i;
}


/* Given a singly linked list, swap kth node from beginning 
 * with kth (k is 1 based) node from end. 
 */
void swapKth (struct node **head, int k) {
    if (k<=0) return;
    if (!head || !*head) return;

    //printf("%s: head:%p k=%d\n", __FUNCTION__, (void *)*head, k);
    int list_size = getListSize(*head);
    if (k > list_size) return;

    if ((list_size/2 == k) && (list_size % 2)) {
        /* middle element */
        printf("same element swaps with itself list_size:%d k:%d\n", 
               list_size, k);
        return;
    }
        
    if (list_size -k < k) {
        k = list_size -k + 1;
    }
    
    struct node *start = *head;
    struct node *end, *curr, *kStart, *prev_kStart, *prev_kEnd, *kEnd;
    
    prev_kStart = prev_kEnd = NULL;
    curr = start;
    int i = 0;

    while (curr) {
        if (i++ == k-1) {
            kStart = curr;
            break;
        }
        prev_kStart = curr;
        curr = curr->next;
    }
    
    kEnd = start;
    
    while (curr) {
        curr = curr->next;
        if (curr) {
            prev_kEnd = kEnd;
            kEnd = kEnd->next;
        }
    }

    if (kStart == prev_kEnd) {
        /* Special case */
        printf("kStart=%p  prev_kEnd=%p k=%d\n",kStart, prev_kEnd, k);
    } 
    {
        if (prev_kStart) {
            prev_kStart->next = kEnd;
        }
        if (prev_kEnd) {
            prev_kEnd->next = kStart;
        }
        struct node *temp = kStart->next;
        kStart->next = kEnd->next;
        kEnd->next = temp;
    }

    if (k == 1) {
        *head = kEnd;
    }
}

int main() {
    // Let us create the following linked list for testing
    // 1->2->3->4->5->6->7->8
    struct node *head = NULL;
    int i, k;
    for (i = 8; i >= 1; i--)
       push(&head, i);
 
    printf("Original Linked List: ");
    printList(head);
    for (k = 1; k < 10; k++) {
        swapKth(&head, k);
        printf("\nModified List for k = %d : ", k);
        printList(head);
    }
 
    return 0;
}
