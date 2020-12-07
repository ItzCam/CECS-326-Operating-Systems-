// Antonio Hughes
// Sandra Chavez
// 10-10-2020
// Prof. Hailu Xu

// Project 2 - Application for Multithreaded Synchronization

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h>
#include "Proj2.h"
#include <time.h>


pthread_cond_t answerCondition, askCondition;
pthread_mutex_t askedLock, answerLock, professorLock, studentLock, globalLock;
sem_t officeSpace;

int asked = 0; // Flag for asked
int answer = 0; // Flag for answer
int askerID; // A global variable for the tracking who is asking questions
int studentID; // Used for the office entry 
int sQuestionID;  
int studentsLeft;
 
// Method for keeping track of the start of a students question
// Note: askerID - global variable
void QuestionStart(){

    printf("Student %d is asking a question.\n", askerID);
}

// Method for keeping track of the end of a students question
// Note: askerID - global variable
void QuestionDone(){

    printf("Student %d is satisfied with the professor's answer\n", askerID);
    usleep(1000);
}

// Method for keeping track of the start of an answer for a student
// Note: askerID - global variable
void AnswerStart(){

        printf("Professor is answering a question for student %d.\n", askerID);
}

// Method for keeping track of the end of a students question and signals when a new question can start
// Note: askerID - global variable
void AnswerDone(){

    printf("The professor is finished answering student %d question.\n", askerID);
    
}

// Method for keeping track of how many students in the prof. office
// Note: studentID - global variable used for office entry
void EnterOffice(){
    
    printf("Student %d has entered the professor's office.\n", studentID);
}

// Method for keeping track of the capacity and room we have for students to enter
// Note: askerID - global variable
void LeaveOffice(){
    
    printf("Student %d is leaving the office.\n", askerID);
}

// Method for locking the global variable to be appended by the current running thread only
// where the parameter is the thread's local id - ID
void askerIDLock(int ID){
    
    pthread_mutex_lock(&globalLock);
        askerID = ID;
        pthread_mutex_unlock(&globalLock);
}

// Method which starts our threads
void *Professor(void* arg){

    // The professor focuses on one student at a time
    pthread_mutex_lock(&studentLock);
    while(studentsLeft > 0){
        pthread_mutex_unlock(&studentLock);
        pthread_mutex_lock(&studentLock);
        pthread_mutex_lock(&askedLock);
        while(!asked){
            pthread_cond_wait(&askCondition, &askedLock);

        if(studentsLeft == 0){

              break;

            }
        }

        asked = 0;
        pthread_mutex_unlock(&askedLock);
        pthread_mutex_lock(&answerLock);
        AnswerStart();
        AnswerDone();
        answer = 1;
        pthread_cond_signal(&answerCondition);
        pthread_mutex_unlock(&answerLock);
        // This is where the professor is finished answering the student's question
        pthread_mutex_unlock(&studentLock);
    }
    pthread_exit(0);
}

// Method creates a new student with a ID. This is ran as a thread through the pthread_create function.
void *Student(void* ID){

    int id = (int)ID;
    int noQuestions;
    // Waiting for office space to open up for a student
    sem_wait(&officeSpace);
    // Set the global identifier for all student threads entering the office
    pthread_mutex_lock(&globalLock);
    studentID = id;
    pthread_mutex_unlock(&globalLock);
    EnterOffice();

    for(noQuestions = (id % 4) + 1; noQuestions > 0; noQuestions--){

        pthread_mutex_lock(&professorLock);
        askerIDLock(id);
        pthread_mutex_lock(&askedLock);
        QuestionStart();
        askerIDLock(id);
        //Setting the flag for the professor
        asked = 1; 
        // signal for question asked
        pthread_cond_signal(&askCondition);
        // let the thread continue
        pthread_mutex_unlock(&askedLock);
        // wait for an answer
        pthread_mutex_lock(&answerLock);
        while(!answer){
            pthread_cond_wait(&answerCondition, &answerLock);
                askerIDLock(id);
        }
        // Satisfactory answer acquired
        QuestionDone();
        pthread_mutex_unlock(&answerLock);
        answer = 0;
        pthread_mutex_unlock(&professorLock);
        usleep(100000);   
    }
    askerIDLock(id);
    LeaveOffice();
    sem_post(&officeSpace);
    studentsLeft--;
    if((studentsLeft == 0)){
        pthread_cond_signal(&askCondition);
    }
    pthread_exit(0);
}

int main(int argc, char * argv[]){

  // Error checking so valid arguments are met
  
  int students;
  int totalStudents;  

  // Checking for proper number of command line arguments
  if(argc < 3 || argc > 3){
	printf("Not enough arguments\n");
	return 2; 
  }

  
  // Check for 0 students
  if(strcmp(argv[1], "0") == 0){
    students = 0;
   
  }else{
    // Check for negative numbers or wrong input values for 1st arg
    students = atoi(argv[1]);
    if(students <= 0){
     	printf("Invalid input!\n");
  	return 1;
    }
  }

  studentsLeft = students;
  totalStudents = students ; 

  // Check for a 0 office capacity
  int officeCapacity;
  if(strcmp(argv[2], "0") == 0){
    printf("Minimum office capacity is 1.\n");
    return 5; 
  }else{
    // Check for negative numbers or wrong input values for 2nd arg
    officeCapacity = atoi(argv[2]);
    if(officeCapacity <= 0){
      printf("Invalid input!\n");
      return 2; 
    }
   }

  // Checks to see if too many threads are called to handle
  if(atoi(argv[1]) > THREADMAX){
    printf("The professor cannot handle that many students\n");
    return 3; 
  }

    

  // Showing how many students we have vs office capacity
  printf("%d student(s) and an office capacity of %d\n", students, officeCapacity);
  
  // Initialize the office space semaphore
  sem_init(&officeSpace, 0, officeCapacity);

  // Initialize the mutex locks 
  pthread_mutex_init(&professorLock, NULL);
  pthread_mutex_init(&answerLock, NULL);
  pthread_mutex_init(&askedLock, NULL);
  pthread_mutex_init(&studentLock, NULL);
  pthread_mutex_init(&globalLock, NULL) ; 

  // Initialize the condition variables 
  pthread_cond_init(&answerCondition, NULL);
  pthread_cond_init(&askCondition, NULL);
  
  // Create the professor thread
  pthread_t professor_tid;
  pthread_create(&professor_tid, NULL, Professor, NULL);
  printf("The professor has entered the office.\n");
  
  // Create student threads
  int i;
  pthread_t studentThreadIDs[students];
  for(i = 0; i < totalStudents; i++){
      pthread_create(&studentThreadIDs[i], NULL, Student, (void*)i);
  }

  int j;
  
  // Wait for all of the students to finish
  for(j = 0; j < totalStudents; j++){
    pthread_join(studentThreadIDs[j], NULL);
  }
  printf("\nAll of the students are finished!\n");

  
  // Wait for the professor to finish
  pthread_join(professor_tid, NULL);
  printf("\nProfessor is going home!\n");

  return 0;
}
