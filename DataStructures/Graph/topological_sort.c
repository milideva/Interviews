#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node_tag node_t;
struct node_tag {
    int vertex;
    bool visited;
    unsigned int num_edges;
    struct node_tag *edges[0]; // edges are assumed Uni-directional, max upto graph->max_edges
};

typedef struct graph_tag graph_t;
struct graph_tag {
    int num_vertices;
    int max_vertices;
    int max_edges; // per vertex
    node_t *vertices[0];
};

node_t *get_vertex (graph_t *graph, int index) {
    if (!graph) return NULL;
    int i, max = graph->max_vertices;
    for (i = 0; i< max; i++) {
        node_t *node = graph->vertices[i];
        if (node && node->vertex == index) {
            printf("get_vertex():%d \n", index);
            return node;
        }
    }
    return NULL;
}

bool find_edge (graph_t *graph, int src_index, int dst_index) {

    if (!graph) return false;

    node_t *src = get_vertex(graph, src_index);
    if (!src) {
        return false;
    }

    node_t *dst = get_vertex(graph, dst_index);
    if (!dst) {
        return false;
    }

    if (!src || !dst) return false;

    for (int i = 0; i < graph->max_edges; i++) {
        node_t *to = src->edges[i];
        if (to && (to == dst)) {
            return true;
        }
    }
    return false;
}

graph_t *create_graph (int max_vertices, int max_edges) {
    if (!max_vertices || !max_edges) return NULL;
    graph_t *graph = calloc(1, sizeof(*graph) + max_vertices * sizeof(graph->vertices[0]));
    if (!graph) return NULL;
    graph->max_vertices = max_vertices;
    graph->max_edges = max_edges;
    printf("Created Graph max_vertices:%d max_edges/vertex:%d \n", max_vertices, max_edges); 
    return graph;
}

node_t *create_vertex (graph_t *graph, int index) {
    if (graph->num_vertices == graph->max_vertices) 
        return NULL;

    node_t *node = calloc(1, sizeof(*node) + sizeof(node->edges[0]) * graph->max_edges );
    if (!node) return NULL;

    node->vertex = index;
    printf("Created Vertex : %d \n", index);
    graph->vertices[graph->num_vertices] = node;
    graph->num_vertices++;

    return node;
}

bool add_edge (graph_t *graph, int src_index, int dst_index) {

    if (!graph) return false;

    node_t *src = get_vertex(graph, src_index);
    if (!src) {
        src = create_vertex(graph, src_index);
    }
    node_t *dst = get_vertex(graph, dst_index);
    if (!dst) {
        dst = create_vertex(graph, dst_index);
    }

    if (!src || !dst) return false;

    if (src->num_edges >= graph->max_edges) return false;
    if (dst->num_edges >= graph->max_edges) return false;

    /* Duplicate edge is not checked for*/
    
    src->edges[src->num_edges] = dst;
    src->num_edges++;
/*
    dst->edges[dst->num_edges] = src;
    dst->num_edges++;
*/
    printf("Created Edge %d <---> %d\n", src_index, dst_index);

    return true;
}

// ///////////////////////// queue code //////////////////////////
typedef struct q_node_tag q_node_t;

struct q_node_tag {
    void *data;
    struct q_node_tag *next;
};

typedef struct q_tag q_t;
struct q_tag {
    q_node_t *head;
    q_node_t *tail;
};

q_t *create_q (void) {
    return calloc(1, sizeof(q_t));
}

/* allocates q_node_t, enqueue at the tail */
void enqueue (q_t *q, void *data) {
    q_node_t *q_node = calloc(1, sizeof *q_node);
    q_node->data = data;
    q_node->next = NULL;

    if (q->tail) {
        q->tail->next = q_node;
    } else {
        q->head = q_node;
    } 
    q->tail = q_node;

    printf("enqueue:tail :%d\n", ((node_t *)data)->vertex); 
}

void *dequeue (q_t *q) {
    q_node_t *head = q->head;
    void *data = NULL;

    if (head) {
        q->head = head->next; // new head
        data = head->data;
        free(head);
        if (q->head == NULL) {
            q->tail = NULL;
        }
        printf("dequeue:%d\n", ((node_t *)data)->vertex);
    }
    return data;
}

void delete_q (q_t *q) {
    q_node_t *next, *curr = q->head;
    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(q);
}

// ///////////////////////// queue code end //////////////////////////


///////////////////////////////////////////////////////////////////
/*
1  procedure BFS(G, start_v) is
2      let Q be a queue
3      label start_v as discovered
4      Q.enqueue(start_v)
5      while Q is not empty do
6          v := Q.dequeue()
7          if v is the goal then
8              return v
9          for all edges from v to w in G.adjacentEdges(v) do
10             if w is not discovered then
11                 w  discovered
13                 Q.enqueue(w) 
*/

bool bfs (graph_t *graph, int src_index, int dst_index) {
    if (!graph) return false;

    node_t *src = get_vertex(graph, src_index);
    node_t *dst = get_vertex(graph, dst_index);

    if (!src || !dst) {
        printf("src:%d %s dst:%d %s\n", src_index, src ? "found" : "not found", dst_index, dst ? "found" : "not found");
        return false;
    }
    if (src == dst) {
        printf("src:%d = dst:%d \n", src_index, dst_index);
        return true;
    }

    printf("BFS src:%d dst:%d \n", src_index, dst_index);

    q_t *q = create_q();
    enqueue(q, src);

    while (q->head) {
        node_t *v = dequeue(q);
        if (v->visited == false) { 
            v->visited = true;
            for (int i = 0; i < graph->max_edges; i++) {
                node_t *to = v->edges[i];
                if (to && (to == dst)) {
                    printf("DFS iterative reaached dst:%d \n", dst_index);
                    delete_q(q);
                    return true;
                }
                if (to && (to->visited == false)) {
                    enqueue(q, to);
                }    
            }
        }
    }
        
    delete_q(q);
    return false;    
}

// ///////////////////////// stack code //////////////////////////

typedef struct stack_node_tag topo_stack_t;

struct stack_node_tag {
    void *data;
    struct stack_node_tag *next;
};

bool push (topo_stack_t **top, void *data) {
    if (!top || !data) return false;
    topo_stack_t *s_node = calloc(1, sizeof *s_node);
    if (!s_node) return NULL;
    s_node->data = data;
    if (*top) {
        s_node->next = *top;
    }
    *top = s_node;
    //printf("push: %d\n", ((node_t *)data)->vertex);
    return true;
}

void *pop (topo_stack_t **top) {
    if (!top || !*top) return NULL;
    topo_stack_t *s_node = *top;
    *top = s_node->next;
    void *ret = s_node->data;
    //printf("pop: %d\n", ((node_t *)ret)->vertex);

    free(s_node);
    return ret;
}

// ///////////////////// stack code end //////////////////////////


void topological_bfs (graph_t *graph, node_t *src, topo_stack_t **top) {
    if (src->visited == true) 
        return;

    src->visited = true;
    //printf("topo_bfs() src: %d\n", src->vertex);

    for (int i = 0; i < graph->max_edges; i++) {
        node_t *to = src->edges[i];
        if (to && (to->visited == false)) {
            topological_bfs(graph, to, top);
        }
    }

    // Done with all dependencies, now put it in stack
    push(top, src);
}

void topological_sort (graph_t *graph) {
    if (!graph) return;
    
    topo_stack_t *topo_stack =  NULL;

    int i, max = graph->max_vertices;
    for (i = 0; i < max; i++) {
        node_t *node = graph->vertices[i];
        if (node && node->vertex != 0) {
            //printf("get_vertex():%d \n", node->vertex);
            if (node->visited == false) {
                topological_bfs(graph, node, &topo_stack);
            }
        }
    }
    while (topo_stack) {
        node_t *node = pop(&topo_stack);
        if (node) {
            printf("topo_order:%d \n", node->vertex);
        }
    }
}

void test1 (void) {
    int max_vertices = 10;
    int max_edges = 5;

    graph_t *graph = create_graph(max_vertices, max_edges);

   /*   
       50           40
      / \         / |
    v    \       /  v
   20     \     /   10
   |         v      |
   |        30      |
   |                |
   |                |
   |                |
   ------> 60 <-----

    */
    add_edge(graph, 40, 10);
    add_edge(graph, 40, 30);
    add_edge(graph, 50, 20);

    add_edge(graph, 50, 30);
    add_edge(graph, 20, 60);
    add_edge(graph, 10, 60);

    topological_sort(graph);
    // visited should be moved to graph so that it can be cleared in one shot

}

int main () {
    test1();
}
