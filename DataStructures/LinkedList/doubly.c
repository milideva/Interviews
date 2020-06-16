#include <stdlib.h>

typedef struct node_tag node_t;

struct node_tag {
    struct node_tag *next;
    struct node_tag *prev;
    int value;
};

typedef int bool;
#define true 1
#define false 0

static node_t *create_node (int data)
{
    node_t *node = calloc(1, sizeof(node_t));
    if (node)
        node->value = data;
    printf("%s: creating node for data:%d\n", __FUNCTION__, data);
    return node;
}

static void print_list (node_t *head)
{
    if (!head) {
        return ;
    }
    node_t *node = head;
    int i = 0;
    printf("%s:\n", __FUNCTION__);
    while (node) {
        printf("[%d] = %d\n", i++, node->value);
        node = node->next;
    }

}

static bool del_node (node_t **head, int value)
{
    if (!head) {
        return false;
    }

    printf("%s: value:%d\n", __FUNCTION__, value);
    node_t *current,*prev; 
    current = *head;
    prev = NULL;
    
    while (current) {
        if (current->value == value) {
            node_t *temp = current;
            current = current->next;
            if (temp == *head) {
                *head = current;
            }
            free(temp);
            if (prev) {
                prev->next = current;
            }
            printf("Found %d ... deleting\n", value); 
        } else {
            prev = current;
            current = current->next;
        }
    }

}
static bool add_node (node_t **head, node_t *node)
{
    if (!head || !node) {
        return false;
    }
    if (!*head) {
        *head = node;
        return true;
    }
    node_t *curr = *head;
    while (curr) {
        if (curr->value > node->value) {
            node->prev = curr->prev;
            node->next = curr;
            curr->prev = node;
            if (curr = *head) *head = node;
            return true;
        }
        if (!curr->next) {
            curr->next = node; node->prev = curr; node->next = NULL;
        }
        curr = curr->next;
    }
    return true;
}

static void test1 (void) 
{
    node_t *head = NULL;
    node_t *my = create_node(5);
    if (!my) 
        return;
    add_node(&head, my);
    my = create_node(6);
    add_node(&head, my);
 
    print_list(head);

    del_node(&head, 5);
    my = create_node(7);
    add_node(&head, my);
    
    print_list(head);
    
}

int main () {

    test1();

    return 0;
}
