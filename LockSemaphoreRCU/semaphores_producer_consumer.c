#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BufferSize 5 

pthread_mutex_t mutex;
sem_t not_full; // init this to non-zero for producer to start producing
sem_t not_empty;
/* Note : No condition variables needed */

int in = 0;
int out = 0;
int buffer[BufferSize];

void *producer (void *pno) {   
    int item;
    while (1) {
      item = rand(); // Produce a random item
      sem_wait(&not_full); // blocks if 0 else decrements
      pthread_mutex_lock(&mutex);
      buffer[in] = item;
      printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
      in = (in+1)%BufferSize;
      pthread_mutex_unlock(&mutex);
      sem_post(&not_empty);
    }
}
void *consumer (void *cno) {   
  while (1) {
    sem_wait(&not_empty);
    pthread_mutex_lock(&mutex);
    int item = buffer[out];
    printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
    out = (out+1)%BufferSize;
    pthread_mutex_unlock(&mutex);
    sem_post(&not_full);
  }
}

int main() {   

    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&not_full, 0, BufferSize); // Note that empty is initialized to BufferSize
    sem_init(&not_empty, 0, 0);

    int a[5] = {1,2,3,4,5}; //Just used for numbering the producer and consumer

    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&not_empty);
    sem_destroy(&not_full);

    return 0;
    
}
