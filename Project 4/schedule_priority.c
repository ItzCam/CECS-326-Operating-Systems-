/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

int tid = 1;
//make a new pointer to the head 
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
    //checks if there is a head 
    while(head != NULL){
        //set both of the pointers to the head
        struct node* current = head;
        struct node* next = head;

	//iterates through the list 
        while (current != NULL){

            //checks if the priority of the current task 
            // is greater than the next priority 
            if(current->task->priority > next->task->priority){

                //sets the next to the current 
                next = current;
            }
            //sets the current node to the next 
            current = current->next;
        }
	//run the task and its burst, then delete the task 
        run(next->task, next->task->burst);
        delete(&head, next->task);
    }
}
