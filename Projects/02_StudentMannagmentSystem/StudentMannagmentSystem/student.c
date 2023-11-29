#include "student.h"

EN_FIFO_RET_t FIFO_Init(ST_FIFO_t* _queue, ST_Student_t* _student, uint32_t _length)
{
	EN_FIFO_RET_t ret = FIFO_NAK;
	if (NULL == _student)
	{
		ret = FIFO_NAK;
	}
	else
	{
		_queue->base = _student;
		_queue->head = _student;
		_queue->tail = _student;
		_queue->lenght = _length;
		_queue->count = 0;
		ret = FIFO_ACK;
	}
	return ret;
}


EN_FIFO_RET_t FIFO_Enqueue(ST_FIFO_t* _queue, ST_Student_t _student)
{
	EN_FIFO_RET_t ret = FIFO_NAK;
	if (NULL == _queue)
	{
		ret = FIFO_NAK;
	}
	else if (FIFO_FULL == FIFO_Is_Full(_queue))
	{
		ret = FIFO_FULL;
	}
	else
	{
		*(_queue->head) = _student;
		_queue->count += 1;
		if (_queue->head == (_queue->base) + (_queue->lenght * sizeof(ST_Student_t)))
		{
			_queue->head = _queue->base;
		}
		else
		{
			_queue->head += 1;
		}
		ret = FIFO_ACK;
	}
	return ret;
}


EN_FIFO_RET_t FIFO_Is_Full(ST_FIFO_t* _queue)
{
	EN_FIFO_RET_t ret = FIFO_NAK;
	if (NULL == _queue)
	{
		ret = FIFO_NAK;
	}
	else
	{
		if (_queue->count == _queue->lenght)
		{
			printf("\n[ERROR] Enqueue Failde ==> Queue Full\n");
			ret = FIFO_FULL;
		}
		else
		{
			ret = FIFO_ACK;
		}
	}
	return ret;
}
