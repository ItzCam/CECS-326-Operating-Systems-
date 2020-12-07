/**
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"


int tid = 1;
struct node* head = NULL;

//Your code and design here
void add(char *name, int priority, int burst){
    Task* t = malloc(sizeof(Task));
    t->name = name;
    t->tid = tid++;
    t->priority = priority;
    t->burst = burst;
    insert(&head, t);
}

void schedule(){
    while(head != NULL){ //if head is not null
        struct node* current = head; //set the temp to the head 
        while (current != NULL){
            if(current->task->burst > QUANTUM){
                //run the task for the quantum 
                run(current->task, QUANTUM);
                // decrement the burst by the quantum 
                current->task->burst -= QUANTUM;
                
            }
            else{
            //run the current task and its remaining burst 
                run(current->task, temp->task->burst);
                //set a new pointer to the current node 
                //to keep track of what you are deleting 
                struct node* remove = current;
                delete(&head, remove->task);
            }
            //set the temp to the next node
            current = current->next;
        }
    }
}
