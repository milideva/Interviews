#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node_ node;

struct node_ {
    int data;
    struct node_ *next;
};


bool push (node **head, int data) {
    if (!head) return NULL;

    node *n = malloc(sizeof(*n));
    if (!n) return false;

    printf("push:%d \n", data); 
    n->data = data;
    n->next = *head;
    *head = n;

    return true;
}

bool pop (node **head, int *data) {
    if (!head || !data || !*head) return false;
    
    node *n = *head;
    *head = n->next;
    *data = n->data;
    printf("pop:%d \n", n->data);
    free(n);
    return true;
}

void printStack (node *head) {
    printf("Stack top : ");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main (void) {
    node *head = NULL;
    int i;
    for (i = 10; i>0; i--) {
        push(&head, i);
    }

    pop(&head, &i);
    printStack(head);
}
