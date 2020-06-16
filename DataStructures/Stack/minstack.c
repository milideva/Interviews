#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>

/* min needs to be in each node and not in stack head.
   This is because pop can take the min elem out
*/
struct node_tag {
    struct node_tag *next;
    int value;
    int min; 
};

typedef struct node_tag node_t;

struct stack_tag {
    node_t *top;
};

typedef struct stack_tag stack_;

/* Implement push/pop/min in O(1) */

static node_t *create_node (int data) {
    node_t *node = calloc(1, sizeof(node_t));
    if (node) 
        node->value = node->min = data;

    return node;
}

static void print_node (node_t *node) {
    if (node)
        printf("stack[] = %d min:%d\n", node->value, node->min);
}

static void print_stack (stack_ *stack) {

    if (!stack) {
        printf("%s: empty stack\n", __FUNCTION__);
        return ;
    }
    node_t *node = stack->top;
    printf("%s: top:%d\n", __FUNCTION__, node->value);
    while (node) {
        print_node(node);
        node = node->next;
    }
}

static stack_ *create_stack (void) {
    stack_ *stack = calloc(1, sizeof(*stack));
    return stack;
}

static void push (stack_ **stack, int data) {
    node_t *node;
    if (!stack) return;

    node = create_node(data);
    if (!node) return;

    if (!*stack) {
        *stack = create_stack();
    }

    node->min = node->value < (*stack)->top->value ? 
        node->value : (*stack)->top->value;
    printf("%s min:%d \n", __FUNCTION__, node->min);
    node->next = (*stack)->top;
    (*stack)->top = node;

    return;
}

static void reverse (stack_ *stack) {
    node_t *curr, *next, *prev = NULL;

    if (!stack) return;
    curr = stack->top;

    while (curr && curr->next) { 
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    curr->next = prev;
    stack->top = curr;
}

static int stack_min (stack_ *stack) {
    if (!stack || !stack->top) return INT_MIN;
    return stack->top->min;
}

static int pop (stack_ **stack) {
    if (!stack || !*stack) return 0;
    node_t *node = (*stack)->top;
    (*stack)->top = node->next;
    int data = node->value;
    free(node);
    return data;
}

static void empty_a_stack (stack_ *stack) {
    if (!stack) return;
    node_t *node = stack->top;
    while (node) {
        int data = pop(&stack);
        printf("POP stack[] = %d min:%d\n", data, 
               stack_min(stack));
        node = stack->top;
    }
}

static stack_ *test_create_a_stack (int num_elements, ...) {
    stack_ *stack = NULL;
    va_list ap;
    int data;

    va_start (ap, num_elements);

    while (num_elements--) {
        data = va_arg(ap, int);
        printf("Got data = %d\n", data);
        //push(&stack, data);
    }
    va_end(ap);
    return stack;
}

/* Create a queue from two stacks */

int main (void) {
    unsigned num_elements = 5;

    stack_ *stack1 = test_create_a_stack(num_elements, 44, 123, 0, 34, -11, -4);
    //print_stack(stack1);
    //empty_a_stack(stack1);
    //reverse(stack1);
    //print_stack(stack1);
    return 0;    
}
