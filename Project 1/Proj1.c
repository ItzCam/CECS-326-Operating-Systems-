/*

Antonio Hughes
Sandra Chavez
CECS 326 - Project 1 - Task 1.1
09-14-2020

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


int SharedVariable = 0;

void* SimpleThread (void *which) // Setting up the pthread function, looked up syntax online
{  

    int number;
    int value;

    int threadID = (int *)which; 

    for (number = 0; number < 20; number++)
    {
        if (random() > RAND_MAX / 2 );
            usleep(500);         //Look up sysntax here - Deals with time lapse

            value = SharedVariable;

            printf("----------------------------------------\n");
            printf("*** Thread %d sees the value of %d\n", threadID, value);
            SharedVariable = value + 1;
    }

    value = SharedVariable;
    printf("Thread %d sees final value %d\n", threadID, value);
}


int main(int argc, char *argv[]){

    if (argc != 2) //Checks the argument count to make sure is valid
    {  
        printf("Invalid number of arguments, please enter one command line parameter");
        return 0;
    }

    int numberOfThreads;
    numberOfThreads = atoi(argv[1]); // This will make the string into an integer
    if(numberOfThreads < 1 )
    {
        printf("Please enter a positive number");
        return(0);
    }

    pthread_t currentThread[numberOfThreads];
    int index[numberOfThreads];
    printf("Size:%d \nnumberofThreads:%d\n", (sizeof(currentThread)/sizeof(currentThread[0])),numberOfThreads); // This will print how many threads we are accesing 

    for(int i = 0; i < numberOfThreads; i++)
    {
        index[i] = i;
        pthread_create(&(currentThread[i]),NULL, SimpleThread, (void *)i); // Lets create the thread now
    }

    
    for(int i = 0; i < numberOfThreads; i++)
    {
        pthread_join(currentThread[i], NULL); // Dont forget to join threads, otherwise it wont work properly
    
    }
}

