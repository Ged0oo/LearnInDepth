#ifndef __QUEUE_LINKED_H__
#define __QUEUE_LINKED_H__

#include <stdio.h>
#include <stdlib.h>

typedef void* QueueEntry_t;

typedef struct queueNode
{
	QueueEntry_t entry;
	struct queueNode* next;
}QueueNode_t;

typedef struct queue
{
	QueueNode_t* front;
	QueueNode_t* rear;
	int size;
}QueueLinked_t;

typedef enum
{
	QUEUE_LINKED_OK = 0,
	QUEUE_LINKED_NULL,
	QUEUE_LINKED_FULL,
	QUEUE_LINKED_EMPTY,
	QUEUE_LINKED_NOT_INTIALIZED
}QueueLinkedReturn_t;

QueueLinkedReturn_t QueueLinkedInit(QueueLinked_t* _queue);
QueueLinkedReturn_t QueueLinkedEmpty(QueueLinked_t* _queue);
QueueLinkedReturn_t QueueLinkedAppend(QueueLinked_t* _queue, QueueEntry_t  _entry);
QueueLinkedReturn_t QueueLinkedServe(QueueLinked_t* _queue, QueueEntry_t* _entry);
						 
QueueLinkedReturn_t QueueLinkedTop(QueueLinked_t* _queue, QueueEntry_t* _entry);
QueueLinkedReturn_t QueueLinkedSize(QueueLinked_t* _queue, int* _size);
QueueLinkedReturn_t QueueLinkedClear(QueueLinked_t* _queue);
QueueLinkedReturn_t QueueLinkedDisplay(QueueLinked_t* _queue);
QueueLinkedReturn_t QueueLinkedTraverse(QueueLinked_t* _queue, void (*pvisit)(QueueEntry_t));

#endif //__QUEUE_LINKED_H__