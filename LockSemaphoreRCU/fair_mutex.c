// This is incomplete.

#include <pthread.h>
struct fair_mutex_ {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    node_t node; // queue. Doubly linked list
};

typedef struct fair_mutex_ fair_mutex_t;

void fair_mutex_lock (fair_mutex_t *fm) {
    pthread_t me =  pthread_self();
    pthread_mutex_lock(&fm->lock);
    enqueue(fm, me); // enqueue at the tail
    while (1) {
        tid = peek(fm); // Look at the head
        if (tid == self) {
            break;
        }
        pthread_cond_wait(&fm->cond, &fm->lock);
    }
    pthread_mutex_unlock(&fm->lock);
}

void fair_mutex_unlock (fair_mutex_t *fm) {
    pthread_t me =  pthread_self();
    pthread_mutex_lock(&fm->lock);
    dequeue(fm, me); // Remove from head
    pthread_cond_broadcast(&fm->cond);
    pthread_mutex_unlock(&fm->lock);
}
