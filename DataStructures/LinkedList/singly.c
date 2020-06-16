#include <stdlib.h>
#include <stdio.h>

#include <time.h>

typedef struct node_tag node_t;

struct node_tag {
    struct node_tag *next;
    int value;
};

typedef enum e_ bool;
enum e_ {
    false,
    true,
};

static node_t *create_node (int data) {
    node_t *node = calloc(1, sizeof(node_t));
    if (node)
        node->value = data;
    return node;
}

/*  Print in reverse without actually reversing it */
static void print_list_reverse (node_t *head, int *i) {
    if (!head || !i) {
        printf("%s:\n", __FUNCTION__);
        return ;
    }
    int num = *i;
    *i += 1;
    print_list_reverse(head->next, i);
    printf("[%d] = %d\n", num, head->value);
}

static void print_node (node_t *node, int i) {
    if (node)
        printf("[%d] = %d\n", i, node->value);
}

static void print_list (node_t *head) {
    if (!head) {
        printf("%s: empty list\n", __FUNCTION__);
        return ;
    }
    node_t *node = head;
    int i = 0;
    printf("%s:\n", __FUNCTION__);
    while (node) {
        print_node(node, i);
        node = node->next;
        i++;
    }
}

/* Example of function pointers / callbacks */

typedef void (*walker_callback) (node_t *node, int i);

void node_walk (node_t *head) {
    walker_callback walker = print_node;
    if (!head) {
        printf("%s: empty list\n", __FUNCTION__);
        return ;
    }
    node_t *node = head;
    int i = 0;
    printf("%s:\n", __FUNCTION__);
    while (node) {
        walker(node, i);
        node = node->next;
    }
}

static bool push (node_t **head, int data) {
    if (!head) return false;

    node_t *n = malloc(sizeof(*n));
    if (!n) return false;

    printf("push:%d \n", data);
    n->value = data;
    n->next = *head;
    *head = n;

    return true;
}

static bool pop (node_t **head, int *data) {
    if (!head || !data || !*head) 
        return false;

    node_t *n = *head;
    *head = n->next;
    *data = n->value;
    printf("pop:%d \n", n->value);
    free(n);
    return true;
}

/* Find if the list is a palindrome.
   1 reverse and check with original.
   2.push first half on stack and compare. saves 50% on space.
   
*/

bool is_palindrome (node_t *head) {
    if (!head) return false;
    node_t *slow, *fast;
    
    node_t *stack = NULL;

    slow = fast = head;
    while (fast && fast->next) {
        push(&stack, slow->value); //create a new node
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast) {
        /* Has odd #elements */
        slow = slow->next;
    }
    while (slow) {
        int top = 0;
        pop(&stack, &top);  // pop: free the top node and return value
        if (top != slow->value) return false;
        slow = slow->next;
    }
    return true;
}

/* Look at the del_node_2 below. Much better way to delete a node in a singly
 linked list (without need to track prev)
*/

static bool del_node (node_t **head, int value) {
    if (!head) {
        return false;
    }

    printf("%s: value:%d\n", __FUNCTION__, value);
    node_t *current,*prev; 
    current = *head;
    prev = NULL;
    
    while (current) {
        if (current->value == value) {
            if (!prev) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Found %d ... deleting\n", value); 
            return true;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return false;
}

/* Without tracking previous! This is much better. */
static bool del_node_2 (node_t **head, int value) {
    if (!head || !*head) {
        return false;
    }

    printf("%s: value:%d\n", __FUNCTION__, value);
    node_t *current,*next; 
    current = *head;

    if (current->value == value) {
        *head = current->next;
        free(current);
        printf("Found %d ... deleting\n", value); 
        return true;
    }
    
    while (current->next) {
        if (current->next->value == value) {
            printf("Found %d ... deleting\n", value); 
            next = current->next->next;
            free(current->next);
            current->next = next;
            return true;
        } 
        current = current->next;
    }
    return false;
}

/*
  Also look at the following.

* Write a function to get the intersection point of two Linked Lists.

http://www.geeksforgeeks.org/write-a-function-to-get-the-intersection-point-of-two-linked-lists/

*/

static void reverse (node_t **head) {
    node_t *prev = NULL;
    node_t *current, *next;

    if (!head || !*head)
        return;
    current = *head;

    printf("In %s:\n", __FUNCTION__);
    while (current) {
        next = current->next; 
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

/* Can not change the API below, is it possible to do recursively? */
/* Can do it if you change the API, return *head  */
static void recursive_reverse (node_t **head) {
    if (!head || !*head) return;

    node_t *curr = *head;
    node_t *next = curr->next;

    if (!next) {
        return;
    }
    recursive_reverse(&(curr->next));
    next->next = curr;
    curr->next = NULL;
    // Can not change head pointer.
}

static bool add_node_unsorted (node_t **head, node_t *node) {
    if (!head || !node) {
        return false;
    }
    node_t *start = *head;

    if (start) {
        node->next = start;
    }
    *head = node;
    printf("%s: value:%d added at head\n", __FUNCTION__, node->value);
    return true;
}
    
static bool add_node (node_t **head, node_t *node) {
    if (!head || !node) {
        return false;
    }
    if (!*head) {
        *head = node;
        printf("%s: value:%d added first\n", __FUNCTION__, node->value);
        return true;
    }
    node_t *current = *head;
    node_t *prev = NULL;
    
    while (current) {
        if (node->value < current->value) {
            if (prev) {
                prev->next = node;
                node->next = current;
            } else { 
                *head = node;
                node->next = current;
            }
            printf("%s: value:%d added\n", __FUNCTION__, node->value);
            return true;
        } else {
            if (node->value == current->value) {
                printf("%s: value:%d duplicate not allowed\n",  
                        __FUNCTION__, node->value);
                return false;
            }
            prev = current;
            current = current->next;
        }
    }

    prev->next = node;
    printf("%s: value:%d added last\n", __FUNCTION__, node->value);
    return true;
}

/* Without tracking prev, this is much better */
bool add_node_2 (node_t **head, node_t *node) {
    if (!head || !node) {
        return false;
    }
    if (!*head) {
        *head = node;
        printf("%s: value:%d added first\n", __FUNCTION__, node->value);
        return true;
    }
    node_t *current = *head;
    if (node->value < current->value) {
        *head = node;
        node->next = current;
        printf("%s: value:%d added\n", __FUNCTION__, node->value);
        return true;
    }

    while (current->next) {
        if (node->value < current->next->value) {
            node->next = current->next;
            current->next = node;
            printf("%s: value:%d added\n", __FUNCTION__, node->value);
            return true;
        } 
        if (node->value == current->value) {
            printf("%s: value:%d duplicate not allowed\n",
                 __FUNCTION__, node->value);
            return false;
        }
        current = current->next;
    }

    current->next = node;
    printf("%s: value:%d added last\n", __FUNCTION__, node->value);
    return true;
}

static bool find_loop (node_t *head)
{
    node_t *slow_ptr = head;
    node_t *fast_ptr = head;
    
    while (slow_ptr  && fast_ptr) {
        fast_ptr = fast_ptr->next;
        if (fast_ptr == slow_ptr) {
            return true; 
        }
        if (fast_ptr == NULL) {
            return false;
        }
        fast_ptr = fast_ptr->next; // Move fast_ptr twice as fast
        /* Compare again */
        if (fast_ptr == slow_ptr) {
            return true;
        }
        slow_ptr = slow_ptr->next;
    }
    return false;
}

/* This is a variation of find_loop, to find start node where the loop
 * starts 
*/
node_t *find_loop_start (node_t *head)
{
    node_t *slow_ptr, *fast_ptr;
    slow_ptr = fast_ptr = head;
    bool loop_flag = false;

    while (slow_ptr && fast_ptr) {
        fast_ptr = fast_ptr->next;
        if (fast_ptr == NULL) {
            return NULL;
        }
        if (fast_ptr == slow_ptr) {
            loop_flag = true;
            break;
        }
        fast_ptr = fast_ptr->next; // Move fast_ptr twice as fast
        /* Compare again */
        if (fast_ptr == slow_ptr) {
            loop_flag = true;
            break;
        }
        slow_ptr = slow_ptr->next;
    }

    if (loop_flag == false) return NULL;
    
    slow_ptr = head;
    /* Move slow to head. Keep fast at Meeting Point. Each are k steps from 
       the Loop Start. If they move at the same pace, they must meet at
       loop start. 
    */
    while (slow_ptr != fast_ptr) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next;
    }
    return slow_ptr;
}

static bool compare_two_lists (node_t *n1, node_t *n2) {

    if (!n1 && !n2) {
        return true; // Both NULL. Both same.
    }

    if (!n1 || !n2) {
        return false; // Only one of them is NULL. Not same.
    }

    if (n1->value != n2->value) {
        return false;
    }

    return compare_two_lists(n1->next, n2->next);
}

static void free_list (node_t **head) 
{
    if (!head)
        return;

    node_t *node = *head;

    if (!node)
        return;

    node_t *next;
    while (node) {
        next = node->next;
        free(node);
        node = next;
    }

    *head = NULL;
    printf("In %s ...done \n", __FUNCTION__);
}

/* Also look at the following

Clone a linked list with next and random pointer 

http://www.geeksforgeeks.org/a-linked-list-with-next-and-arbit-pointer/

1) Create the copy of node 1 and insert it between node 1 & node 2 in original
Linked List, create the copy of 2 and insert it between 2 & 3.. Continue in
this fashion, add the copy of N afte the Nth node
2) Now copy the arbitrary link in this fashion

     original->next->arbitrary = original->arbitrary->next; 

This works because original->next is nothing but copy of original and Original->arbitrary->next is nothing but copy of arbitrary.

3) Now restore the original and copy linked lists in this fashion in a single loop.
     original->next = original->next->next;
     copy->next = copy->next->next;

4) Make sure that last element of original->next is NULL.
*/

static void copy_linked_list (node_t *src, node_t **dest)
{
    if (src) {
        *dest = calloc(1, sizeof(node_t)); /* This writes head, next of prev */
        (*dest)->value = src->value;
        (*dest)->next = NULL;
        copy_linked_list(src->next, &((*dest)->next));
    }
}

/* Merge two sorted linked lists */
node_t* merge (node_t *head1, node_t *head2) { 
    node_t *it1, *it2, *head; // two iterators and a new head to return
    
    if (!head1) 
        return head2;

    if (!head2) 
        return head1;

    head = (head1->value <= head2->value) ? head1 : head2;
    
    if (head == head1) { 
        it1 = head1; 
        it2 = head2;
    } else {
        it1 = head2;
        it2 = head1;
    }
    // Keep it1 smaller than it2
    while (it1->next && it2){
        if (it1->next->value > it2->value){
            node_t *temp = it1->next;
            it1->next = it2;
            it2 = temp;
        } else{
            it1 = it1->next;
        }
    }

    if (it2)
        it1->next = it2;

    return head;
}

/* Remove all duplicates from SORTED singly linked list */
void remove_duplicates_sorted (node_t *head) {
    if (!head) return;

    node_t *curr = head;

    while (curr->next) {
        if (curr->next->value == curr->value) {
            node_t *next_next = curr->next->next;
            free(curr->next);
            curr->next = next_next;
            continue;
        } else {
            curr = curr->next;
        }
    }
}

/* Remove all duplicates from an UNSORTED singly linked list */
static void remove_duplicates_unsorted (node_t *head) {
    node_t *n1, *n2;
    
    if (!head) return;

    n1 = head;
    
    while (n1 && n1->next) {
        n2 = n1;
        while (n2->next) {
            if (n1->value == n2->next->value) {
                node_t *dup = n2->next;
                n2->next = n2->next->next;
                free(dup);
                continue;
            }
            n2 = n2->next;
        }
        n1 = n1->next;
    }
}

/* Rotate list 
   Given a list, rotate the list to the right by k places, 
   For example:
   Given 1->2->3->4->5->NULL and k = 2,
   return 4->5->1->2->3->NULL.
*/

static bool rotate_list (node_t **head, unsigned int k) {
    if (!head || !*head) return false;
    node_t *curr, *new_tail, *prev;
    curr = new_tail = *head;
    prev = NULL;

    printf("%s by %u\n", __FUNCTION__, k);
    while (k) {
        if (!curr) {
            return false;
        }
        curr = curr->next;
        k--;
    }
    
    /* now curr is k nodes away from head*/
    while (curr->next) {
        curr = curr->next;
        new_tail = new_tail->next;
    }
    curr->next = *head;
    *head =  new_tail->next;
    new_tail->next = NULL;
    
    return true;
}

/* Return kth from last */
node_t *kth_from_last (node_t *head, unsigned int k) {
    node_t *slow, *fast;
    fast = head;
    while (k-- && fast) {
        fast = fast->next;
    }
    if (k && !fast) return NULL;

    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

/* Remove middle element */
static node_t *remove_middle (node_t *head) {
    node_t *slow, *fast, *prev;
    prev = slow = fast = head;

    while (fast) {
        fast = fast->next;
        if (fast) {
            fast = fast->next;
        } 
        prev = slow;
        slow = slow->next;
    }
    node_t *middle = prev->next;
    prev->next = prev->next->next;
    return middle;
}

/******************************  Test code *******************************/
static node_t *build_list (int start, int end, int step, 
                           bool random, bool sorted) 
{

    int min = (start < end) ? start : end;
    int max = (start < end) ? end : start;

    int num = (max - min) / step;

    node_t *head = NULL;

    printf("%s: creating list start:%d end:%d step:%d random:%d\n",
           __FUNCTION__, start, end, step, random);

    if (random) {
        unsigned int iseed = (unsigned int)time(NULL);
        srand (iseed);
    }

    int i;
    for (i = 0; i < num; i++) {
        int value;
        node_t *my;

        if (!random) {
            value = min + i * step;
        } else {
            value = (rand() % (max - min)) + min;
        }
        my = create_node(value);
        if (sorted) 
            add_node(&head, my);
        else 
            add_node_unsorted(&head, my);
    }

    return head;
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
    
    my = create_node(17);
    add_node(&head, my);
    
    my = create_node(7);
    add_node(&head, my);
    
    my = create_node(1);
    add_node(&head, my);
    
    my = create_node(7);
    if (!add_node(&head, my))
        del_node(&head, my->value);
    add_node(&head, my);
        
    print_list(head);

    int i=0;
    print_list_reverse(head, &i);

    //recursive_reverse(&head);
    reverse(&head);
    print_list(head);

    del_node_2(&head, 17);
    print_list(head);

    del_node_2(&head, 1);
    print_list(head);

    my = create_node(5);
    add_node_unsorted(&head, my);
     
    del_node_2(&head, 5);
    print_list(head);

    my = create_node(15);
    add_node_unsorted(&head, my);

    my = create_node(7);
    my = create_node(6);
    del_node_2(&head, 6);
    print_list(head);

    my = create_node(15);
    add_node_unsorted(&head, my);
    
    my = create_node(7);
    add_node_unsorted(&head, my);
    
    my = create_node(1);
    add_node_unsorted(&head, my);
    
    my = create_node(7);
    add_node_unsorted(&head, my);

    my = create_node(17);
    add_node_unsorted(&head, my);
    
    my = create_node(1);
    add_node_unsorted(&head, my);
   
    print_list(head);
    remove_duplicates_unsorted(head);
    print_list(head);

    my = create_node(27);
    add_node_unsorted(&head, my);
    print_list(head);
    rotate_list(&head, 2);
    print_list(head);

    node_t *head1, *head2;
    printf("Calling copy_linked_list()\n");
    copy_linked_list(head, &head2);
    print_list(head2);
    return;

    free_list(&head);

    print_list(head);

    head1 = build_list(0, 25, 5, 0, 1);
    printf("Merge list 1: \n");
    print_list(head1);

    head2 = build_list(6, 25, 2, 1, 1);
    printf("Merge list 2: \n");
    print_list(head2);

    node_t *head3 = merge(head1, head2);
    printf("Merged list: \n");
    print_list(head3);
}

int main () {

    test1();

    return 0;
}
