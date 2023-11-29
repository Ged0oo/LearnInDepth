#ifndef  __STUDENT_H__
#define	__STUDENT_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define flush fflush(stdin); fflush(stdout)

#define MAX_NAME_LENGTH		25
#define COURSES_NUMBER		5
#define	MAX_STUDENT_NUMER	50

typedef struct student
{
	int rollNumber;
	char firstName[MAX_NAME_LENGTH];
	char lastName[MAX_NAME_LENGTH];
	float gpa;
	int courseID[COURSES_NUMBER];
}ST_Student_t;

typedef struct fifo
{
	ST_Student_t* base;
	ST_Student_t* head;
	ST_Student_t* tail;
	int lenght;
	int count;
}ST_FIFO_t;

typedef enum
{
	FIFO_ACK,
	FIFO_NAK,
	FIFO_FULL,
	FIFO,EMPTY
}EN_FIFO_RET_t;

EN_FIFO_RET_t FIFO_Init(ST_FIFO_t* _queue, ST_Student_t* _student, uint32_t _length);	    
EN_FIFO_RET_t FIFO_Enqueue(ST_FIFO_t* _queue, ST_Student_t _student);
EN_FIFO_RET_t FIFO_Is_Full(ST_FIFO_t* _queue);

EN_FIFO_RET_t Student_Add_Manually(ST_FIFO_t* _queue);
EN_FIFO_RET_t Student_Add_From_File(ST_FIFO_t* _queue);
ST_Student_t* Check_Student_ID(ST_FIFO_t* _queue, int _id);

void Find_StudentFrom_ID(ST_FIFO_t* _queue);
void Find_Student_From_FirstName(ST_FIFO_t* _queue);
void Find_Student_From_Course_ID(ST_FIFO_t* _queue);

void Delete_Student_With_ID(ST_FIFO_t* _queue);
void Update_Student_With_ID(ST_FIFO_t* _queue);
void Print_Student(ST_Student_t* _student);
void Print_Student_Count(ST_FIFO_t* _queue);
void Show_Student_Data_Base(ST_FIFO_t* _queue);

#endif // ! __STUDENT_H__
