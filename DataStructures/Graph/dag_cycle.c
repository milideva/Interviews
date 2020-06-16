#include <stdio.h>

/* Code is incomplete */

typedef struct node_ node;
typedef struct graph_ graph;

struct node_ {
    int id;
    struct node_ *next;
};

struct graph_ {
    int vertices;
    struct node_ **adj_list;
    bool visited[vertices];
};


graph *init_graph (int num_nodes) {
    graph *g = malloc(sizeof *g);
    g->vertices = num_nodes;
    g->adj_list = malloc(num_nodes * sizeof *adj_list);
    memset(g->adj_list, 0, num_nodes * sizeof *adj_list);

    int i;
    for (i=0; i < num_nodes; i++) {
        node *n = malloc(sizeof *n);
        g->adj_list[i] = n;
        n->id = i;
        n->next = NULL;
    }
    return g;
}

void add_edge (graph *g, int src, int dest) {
    node *temp;
    temp=  malloc(sizeof(struct node));
    temp->id = dest;
    temp->next = g->adj_list[src]; // Add the new edge of dest node in front
    g->adj_list[src] = temp;
}
                                          
                                          
bool dfs (int id, graph *g) {
    struct node *curr;

    if (g->visited[id]) {
        return true;
    }
    
    printf("visiting %d\n",id);
    g->visited[id] =  true;

    curr = g->adj_list[x];
    while (curr) {
        dfs(curr->id, g);
        curr = curr->next;
    }

    return false;
}
