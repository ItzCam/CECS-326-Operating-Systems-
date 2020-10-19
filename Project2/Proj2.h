#define THREADMAX	10000 /*the max amount of runtime-threads that can be initialized*/
#define OFFICECAP	50

void *professor(void*);
void *Student(void*) ; 
void AnswerStart();
void AnswerDone(); 
void EnterOffice();
void LeaveOffice();
void QuestionStart();
void QuestionDone(); 
void askerIdLock(int);
