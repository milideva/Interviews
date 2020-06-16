#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node_ node_t;
struct node_ {
    int key;
    struct node_ *left, *right;
};

node_t *create_node (int key) {
    node_t *n = calloc(1, sizeof *n);
    if (!n) return NULL;
    n->key = key;
    return n;
}

// 1 based
int get_tree_height (node_t *root) {
    if (!root) return 0;
    int left_height = get_tree_height(root->left);
    int right_height = get_tree_height(root->right);
    int max = left_height >  right_height ? left_height : right_height;
    return max + 1;
}

//////////// queue implementation ////////
typedef struct qnode_ qnode_t;
struct qnode_ {
    void *data;
    struct qnode_ *next;
};

qnode_t *create_qnode (void *data) {
    qnode_t *qn = calloc(1, sizeof *qn);
    if (qn) qn->data = data;
    return qn;    
}

void enqueue (qnode_t **head, void *data) {
    if (!head || !data) return;
    qnode_t *start = *head;

    qnode_t *qn = create_qnode(data);
    if (!start) {
        *head = qn;
        return;
    }
    qn->next = start;
    *head = qn;
    return;
}

void *dequeue (qnode_t **head) {
    if (!head) return NULL;

    qnode_t *start = *head;
    if (!start) return  NULL;
    *head = start->next;
    void *data = start->data;
    free(start);
    return data;
}

bool empty (qnode_t *head) {
    if (head && head->data) return false;
    return true;
}

//////////// end of queue implementation ////////////////

void bfs_avg (node_t *root, double *arr, int *arr_size) {
    if (!root) return;
    int i = 0;

    qnode_t *sum_queue = NULL;
    enqueue(&sum_queue, root);
    while (!empty(sum_queue)) {
        int count, sum;
        count = sum = 0;
        qnode_t *level_queue = NULL;
        while (!empty(sum_queue)) {
            node_t *n = dequeue(&sum_queue);
            if (n->left) enqueue(&level_queue, n->left);
            if (n->right) enqueue(&level_queue, n->right);
            sum += n->key;
            count += 1;
        }
        arr[i++] = sum * 1.0 / count;
        sum_queue = level_queue;
    }
    *arr_size = i;
    return;
    /* pseudo code
    queue_init(sum_queue);
    enqueue(sum_queue, root);
    while (!empty(sum_queue)) {
        int count, sum;
        count = sum = 0;
        queue_init(level_queue);
        while (!empty(sum_queue)) { 
            node = dequeue(sum_queue)
            if (node->left) enqueue(level_queue, node->left);
            if (node->right) enqueue(level_queue, node->right);
            sum += node->key;
            count += 1;
        }
        arr[i++] = sum * 1.0 / count;
        sum_queue = level_queue;
    }

    return arr

*/
}

double *get_avg_level (node_t *root, int *num_nodes) {
    int height = get_tree_height(root);
    printf("height:%d\n", height);
    double *arr = calloc(height,  sizeof *arr);
    bfs_avg(root, arr, num_nodes);
    printf("num_levels:%d\n", *num_nodes);
    return arr;
}

int main (void) {
    node_t *root = create_node(50);
    root->left = create_node(10);
    root->right = create_node(40);
    root->left->right = create_node(20);
    root->left->left = create_node(80);
    root->right->left = create_node(50);
    

    int num_levels = 0;

    double *avg = get_avg_level(root, &num_levels);
    for (int i = 0; i < num_levels; i++) {
        printf("level:%d avg:%f\n", i, avg[i]);
    }
    return 0;
}
