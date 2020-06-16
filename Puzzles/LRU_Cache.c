#include <stdlib.h>
#include <stdio.h>

typedef struct cache_line_ cache_line;

struct cache_line_ {
    cache_line *prev, *next;
    unsigned int cache_tag;
    unsigned data[64];
};

// find cache_tag
// if found, remove and add to the front
// if not found, create cache_line, add to front if size of cache < MAX_CACHE
// else, remove cache_line from tail (LRU).

typedef struct cache_ cache;

struct cache_ {
    unsigned max_cache_lines;
    unsigned count;
    cache_line *head, *tail;
};

cache *create_cache (unsigned max_cache_lines) {

    if (!max_cache_lines) 
        return NULL;

    cache *c;
    size_t size = sizeof(*c);

    c = calloc(1, size);
    if (c) { 
        c->max_cache_lines = max_cache_lines;
    }
    return c;
}

cache_line *allocate_cacheline (unsigned cache_tag) {
    cache_line *n = calloc(1, sizeof(*n));
    if (n) n->cache_tag = cache_tag;
    return n;
}

/* Search takes O(N), consider moving this to a hash map for O(log n) */
cache_line *search_cache (cache *c, unsigned cache_tag) {
    if (!c) return NULL;

    cache_line *n = c->head;
    while (n) {
        if (n->cache_tag == cache_tag) 
            return n;
        n = n->next;
    }
    return NULL;
}

cache_line *dequeue_cache_line (cache *c, cache_line *n) {
    if (!c->count || !n) {
        printf("%s: no elements\n", __FUNCTION__);
        return NULL;
    }
    c->count--;
    if (n->prev) {
        n->prev->next = n->next;
    }
    if (n->next) {
        n->next->prev = n->prev;
    }
    if (c->head == n) {
        c->head = n->next;
    }
    if (c->tail == n) {
        c->tail = n->prev;
    }
    n->next = n->prev = NULL;
    return n;
}

void enqueue_cache_line (cache *c, cache_line *n) {
    if (!c->count) {
        c->head = c->tail = n;
        c->count++;
        return;
    }
    if (c->count == c->max_cache_lines) {
        cache_line *n_tail = dequeue_cache_line(c, c->tail);
        /* Handle removed cache_line */        
    }
    c->count++;
    n->next = c->head;
    c->head->prev = n;
    c->head = n;
}

cache_line *lookup_cache (cache *c, unsigned cache_tag) {
    cache_line *n = search_cache(c, cache_tag);
    if (!n) {
        n = allocate_cacheline(cache_tag);
        enqueue_cache_line(c, n);
        return n;
    }
    n = dequeue_cache_line(c, n);
    enqueue_cache_line(c, n);
    return n;
}

void print_cache (cache *c) {
    cache_line *n = c->head;
    printf("CACHE: %d elements head: ", c->count);
    while (n) {
        printf("%d ", n->cache_tag);
        n = n->next;

    }
    printf(" tail ");
    printf(":::::: head:%d tail:%d\n", c->head ? c->head->cache_tag : 0,
           c->tail ? c->tail->cache_tag : 0);

}

int main (void) {
    cache *c = create_cache(64);
    int i;
    lookup_cache(c, 1);
    lookup_cache(c, 2);
    lookup_cache(c, 1);
    lookup_cache(c, 5);
    print_cache(c);
    for (i=1; i< 100; i++) {
        lookup_cache(c, i);
    }
    print_cache(c);
}
