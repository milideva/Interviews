
#include <stdio.h>
#include <pthread.h>

#define MAX (10000000000)			/* Numbers to produce */
pthread_mutex_t the_mutex;
pthread_cond_t cond_c, cond_p;
int buffer = 0;

void* producer (void *ptr) {
  int i;

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);
    while (buffer != 0)	{
      pthread_cond_wait(&cond_p, &the_mutex);
    }
    buffer = i;
    pthread_cond_signal(&cond_c);
    pthread_mutex_unlock(&the_mutex);
  }
  pthread_exit(0);
}

void* consumer (void *ptr) {
  int i;

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);
    while (buffer == 0) {
      pthread_cond_wait(&cond_c, &the_mutex);
    }
    buffer = 0;
    pthread_cond_signal(&cond_p);
    pthread_mutex_unlock(&the_mutex);
  }
  pthread_exit(0);
}

int main(int argc, char **argv) {
  pthread_t pro, con;
  const pthread_mutexattr_t *mutex_attr = NULL;
  const pthread_condattr_t *cond_attr = NULL;
  const pthread_attr_t *thread_attr = NULL;
  void *arg = NULL;

  pthread_mutex_init(&the_mutex, mutex_attr);	
  pthread_cond_init(&cond_c, cond_attr);
  pthread_cond_init(&cond_p, cond_attr);

  pthread_create(&con, thread_attr, consumer, arg);
  pthread_create(&pro, thread_attr, producer, arg);


  pthread_join(&con, NULL);
  pthread_join(&pro, NULL);

  pthread_mutex_destroy(&the_mutex);
  pthread_cond_destroy(&cond_c)
  pthread_cond_destroy(&cond_p);

}
