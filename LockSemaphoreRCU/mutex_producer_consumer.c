#include <stdio.h>
#include <pthread.h>

#define BUFF_SIZE 10

int buf_index = 0;
char buffer[BUFF_SIZE];

/* 
Mutex lock is for mutual exclusion.
Condition variable is for signalling or synchronization and waiting on a
condition for a wake up
*/
pthread_cond_t cond_Not_Full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_Not_Empty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *Producer (void *arg) {    

  while (1) {
    pthread_mutex_lock(&mutex);
    while (buf_index == BUFF_SIZE) { // This needs to be a while instead of a if for multiple producers.                       
      pthread_cond_wait(&cond_Not_Full, &mutex);
    }                        
    buffer[buf_index++]='@';
    printf("Produce : %d \n", buf_index);
    pthread_cond_signal(&cond_Not_Empty);
    pthread_mutex_unlock(&mutex);
  }    
    
}

/* Q1 : Is it ok to call pthread_cond_signal() after pthread_mutex_unlock() 
It is suboptimal to do so. 
If you signal before the unlock, the implementation knows the signal can't
possibly wake a thread (because any thread blocked on the cv needs the mutex to
make forward progress), allowing it to use the fast path. If you signal after
the unlock, both the unlock and the signal can wake threads, meaning they're
both expensive operations.
*/

void *Consumer (void *arg) {

  while (1) {
    pthread_mutex_lock(&mutex);
    while (buf_index <= 0) {            
      pthread_cond_wait(&cond_Not_Empty, &mutex);
    }
    buf_index--;
    printf("Consume : %d \n", buf_index);        
    pthread_cond_signal(&cond_Not_Full);
    pthread_mutex_unlock(&mutex);        
  }    

}

/* Q2 : is it ok to call pthread_cond_wait() without lock() / unlock() ?
NO.

- Process A:

while (condition == FALSE)
    pthread_cond_wait(&cond, &mutex);

- Process B (incorrect):

condition = TRUE;
pthread_cond_signal(&cond);

Then consider this possible interleaving of instructions, where condition starts out as FALSE:

Process A                             Process B

while (condition == FALSE)

                                      condition = TRUE;
                                      pthread_cond_signal(&cond);

pthread_cond_wait(&cond, &mutex);
The condition is now TRUE, but Process A is stuck waiting on the condition
variable - it missed the wakeup signal. 

*/ 

/*
More reading
https://stackoverflow.com/questions/4544234/calling-pthread-cond-signal-without-locking-mutex

The pthread_cond_broadcast() or pthread_cond_signal() functions may be called
by a thread whether or not it currently owns the mutex that threads calling
pthread_cond_wait() or pthread_cond_timedwait() have associated with the
condition variable during their waits; however, if predictable scheduling
behavior is required, then that mutex shall be locked by the thread calling
pthread_cond_broadcast() or pthread_cond_signal().

The meaning of the predictable scheduling behavior statement was explained by
Dave Butenhof (author of Programming with POSIX Threads) on
comp.programming.threads and is available here.

*/

int main() {    
    pthread_t ptid,ctid;
    pthread_attr_t *attr = NULL;
    void *arg = NULL;

    pthread_cond_init(&cond_Not_Full, NULL);
    pthread_cond_init(&cond_Not_Empty, NULL);

    pthread_create(&ptid, attr, Producer, arg);
    pthread_create(&ctid, attr, Consumer, arg);
    
    pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);
    
    return 0;
}


/*
https://github.com/angrave/SystemProgramming/wiki/Synchronization,-Part-5:-condition-Variables

(Advanced topic) Why do condition Variables also need a mutex?
condition variables need a mutex for three reasons. 

The simplest to understand is that it prevents an early wakeup message (signal
or broadcast functions) from being 'lost.' Imagine the following sequence of
events (time runs down the page) where the condition is satisfied just before
pthread_cond_wait is called.
(answer was 41)
then Thread2 runs and makes it 42.
but now Thread1 runs and will be blocked on wait (until thread2 increments again)
When thread2 makes it 42 and signals cond, Thread1 NOT waiting on it yet.

In this example the wake-up signal is lost!

Thread 1	                            Thread 2

while (answer < 42) {	 

 	                                    answer++
 	                                    p_cond_signal(cv)

p_cond_wait(cv, m)	 

If both threads had locked a mutex, the signal can not be sent until after
pthread_cond_wait(cv, m) is called (which then internally unlocks the mutex)

A second common reason is that updating the program state (answer variable)
typically requires mutual exclusion - for example multiple threads may be
updating the value of answer.

A third and subtle reason is to satisfy real-time scheduling concerns which we
only outline here: In a time-critical application, the waiting thread with the
highest priority should be allowed to continue first. To satisfy this
requirement the mutex must also be locked before calling pthread_cond_signal or
pthread_cond_broadcast 


*/


