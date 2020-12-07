/**
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

//Your code and design here

//sets a pointer to the head
struct node* head = NULL;
int id = 1; 

void add(char *name, int priority, int burst) {

    //make a new task 
    Task* t = malloc(sizeof(Task));
    t->name = name;
    t->priority = priority;
    t->burst= burst;
    t->tid = id++;

    insert(&head, t);

}


void schedule(){
    //checks if the head exists in the list 
    while(head != NULL){

	//sets the current pointer to the head
        struct node* current = head;

        //iterates through the list 
        while(current->next != NULL){
            current = current->next;
        }
        //runs the task and deletes it 
        run(current->task, current->task->burst);
        delete(&head, current->task);
    }
}
