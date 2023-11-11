#include "QueueLinked.h"


static QueueNode_t* createNode(QueueEntry_t _entry);


QueueLinkedReturn_t QueueLinkedInit(QueueLinked_t* _queue)
{
	QueueLinkedReturn_t ret = QUEUE_LINKED_OK;
	if (NULL == _queue)
	{
		ret = QUEUE_LINKED_NULL;
	}
	else
	{
		_queue->front = NULL;
		_queue->rear = NULL;
		_queue->size = 0;
		ret = QUEUE_LINKED_OK;
	}
	return ret;
}


QueueLinkedReturn_t QueueLinkedEmpty(QueueLinked_t* _queue)
{
	QueueLinkedReturn_t ret = QUEUE_LINKED_OK;
	if (NULL == _queue)
	{
		ret = QUEUE_LINKED_NULL;
	}
	else
	{
		if (0 == _queue->size)
		{
			ret = QUEUE_LINKED_EMPTY;
		}
		else { /* Nothing */ }
	}
	return ret;
}


QueueLinkedReturn_t QueueLinkedAppend(QueueLinked_t* _queue, QueueEntry_t  _entry)
{
	QueueLinkedReturn_t ret = QUEUE_LINKED_OK;
	if (NULL == _queue)
	{
		ret = QUEUE_LINKED_NULL;
	}
	else
	{
		QueueNode_t* newNode = createNode(_entry);

		if (QUEUE_LINKED_EMPTY == QueueLinkedEmpty(_queue))
		{
			_queue->front = newNode;
			_queue->rear = newNode;
		}
		else
		{
			_queue->rear->next = newNode;
			_queue->rear = newNode;
		}
				
		_queue->size += 1;
		ret = QUEUE_LINKED_OK;
	}
	return ret;
}


QueueLinkedReturn_t QueueLinkedServe(QueueLinked_t* _queue, QueueEntry_t* _entry)
{
	QueueLinkedReturn_t ret = QUEUE_LINKED_OK;
	if (NULL == _queue)
	{
		ret = QUEUE_LINKED_NULL;
	}
	else if (QUEUE_LINKED_EMPTY == QueueArrayEmpty(_queue))
	{
		ret = QUEUE_LINKED_EMPTY;
	}
	else
	{
		QueueNode_t* newNode = _queue->front;
		*_entry = newNode->entry;
		_queue->front = newNode->next;
		free(newNode);
		if (NULL == _queue->front)
			_queue->rear = NULL;
		_queue->size -= 1;
		ret = QUEUE_LINKED_OK;
	}
	return ret;
}


QueueLinkedReturn_t QueueLinkedTop(QueueLinked_t* _queue, QueueEntry_t* _entry)
{
	QueueLinkedReturn_t ret = QUEUE_LINKED_OK;
	if (NULL == _queue)
	{
		ret = QUEUE_LINKED_NULL;
	}
	else if (QUEUE_LINKED_EMPTY == QueueArrayEmpty(_queue))
	{
		ret = QUEUE_LINKED_EMPTY;
	}
	else
	{
		*_entry = _queue->front->entry;
		ret = QUEUE_LINKED_OK;
	}
	return ret;
}


QueueLinkedReturn_t QueueLinkedSize(QueueLinked_t* _queue, int* _size)
{
	QueueLinkedReturn_t ret = QUEUE_LINKED_OK;
	if (NULL == _queue)
	{
		ret = QUEUE_LINKED_NULL;
	}
	else
	{
		*_size = _queue->size;
		ret = QUEUE_LINKED_OK;
	}
	return ret;
}


QueueLinkedReturn_t QueueLinkedClear(QueueLinked_t* _queue)
{
	QueueLinkedReturn_t ret = QUEUE_LINKED_OK;
	if (NULL == _queue)
	{
		ret = QUEUE_LINKED_NULL;
	}
	else if (QUEUE_LINKED_EMPTY == QueueLinkedEmpty(_queue))
	{
		ret = QUEUE_LINKED_EMPTY;
	}
	else
	{
		while (NULL != _queue->front)
		{
			_queue->rear = _queue->front->next;
			free(_queue->front);
			_queue->front = _queue->rear;
		}
		_queue->size = 0;
		ret = QUEUE_LINKED_OK;
	}
	return ret;
}


QueueLinkedReturn_t QueueLinkedDisplay(QueueLinked_t* _queue)
{
	QueueLinkedReturn_t ret = QUEUE_LINKED_OK;
	if (NULL == _queue)
	{
		ret = QUEUE_LINKED_NULL;
	}
	else if (QUEUE_LINKED_EMPTY == QueueLinkedEmpty(_queue))
	{
		ret = QUEUE_LINKED_EMPTY;
	}
	else
	{
		printf("\nQueue Display\n[ ");
		QueueNode_t* newNode = _queue->front;
		while (newNode != NULL)
		{
			printf(" %d ", newNode->entry);
			newNode = newNode->next;
		}
		printf(" ]\n");
		ret = QUEUE_LINKED_OK;
	}
	return ret;
}


QueueLinkedReturn_t QueueLinkedTraverse(QueueLinked_t* _queue, void (*pvisit)(QueueEntry_t))
{
	QueueLinkedReturn_t ret = QUEUE_LINKED_OK;
	if (NULL == _queue)
	{
		ret = QUEUE_LINKED_NULL;
	}
	else if (QUEUE_LINKED_EMPTY == QueueLinkedEmpty(_queue))
	{
		ret = QUEUE_LINKED_EMPTY;
	}
	else
	{
		QueueNode_t* newNode = _queue->front;
		for (newNode ; newNode != NULL; newNode->next)
			(*pvisit)(newNode->entry);
		ret = QUEUE_LINKED_OK;
	}
	return ret;
}


static QueueNode_t* createNode(QueueEntry_t _entry)
{
	QueueNode_t* newNode = (QueueNode_t*)malloc(sizeof(QueueNode_t));
	if (newNode == NULL)
	{
		printf("Memory allocation failed.\n");
		exit(1);
	}
	else
	{
		newNode->entry = _entry;
		newNode->next = NULL;
		return newNode;
	}
}
