/*

Antonio Hughes
Sandra Chavez
CECS 326 - Project 1 - Task 1.2
09-14-2020

*/


#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

#define NUMTHREADS 5 // This is command line argument.

int SharedVariable = 0;
pthread_mutex_t lock;
pthread_barrier_t barr;

void* SimpleThread(void *which) {

int number;
int value;

int threadID = *(int*)which;

for(number = 0; number < 20; number++) {    // Same set up as task 1 

#ifdef PTHREAD_SYNC
pthread_mutex_lock(&lock);  // Mutex locks the thread, enables synchronization to take place
#endif

printf("thread %d sees value %d\n", threadID, SharedVariable); //Incrementing the shared variable here 
SharedVariable++;

#ifdef PTHREAD_SYNC
pthread_mutex_unlock(&lock);  // Mutex unlocks the thread, lets in more threads to be accessed 
#endif

}

pthread_barrier_wait(&barr);  // barrier so that all thread will read the shared variable value and display the final value.
printf("Thread %d sees final value %d\n", threadID,SharedVariable);
return NULL;

}

int main() {

int index;
int error;

// NUMTHREADS is 5

pthread_t threads[NUMTHREADS];
int threadIDs[NUMTHREADS]={0};

// initialixing the mutex.
pthread_mutex_init(&lock, NULL);

// initialixing barrier.
pthread_barrier_init(&barr, NULL, NUMTHREADS);

for(index = 0; index < NUMTHREADS; index ++)
    {
        threadIDs[index]=index; // giving thread ID's
        
        error = pthread_create(&threads[index], NULL, SimpleThread, (void*)&threadIDs[index]); // creating threads
        
        if(error)
        {
            printf("ERROR creating THREADS, return code %d\n",error);
            exit(-1);
            }
            
    }
    
    for(index = 0; index < NUMTHREADS; index++) // For loop to process and wait for all the threads to finish printint their values
    {
        pthread_join(threads[index], NULL);
        
        }


return 0;

}