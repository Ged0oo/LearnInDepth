#ifndef  __STUDENT_H__
#define	__STUDENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

#endif // ! __STUDENT_H__
