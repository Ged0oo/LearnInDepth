#include "StackLinked.h"



static StackNode_t* createNode(StackEntry_t _entry);


StackReturn_t StackLinkedInit(StackLinked_t* _stack)
{
	StackReturn_t ret = STACK_LINKED_OK;
	if (NULL == _stack)
	{
		ret = STACK_LINKED_NULL;
	}
	else
	{
		_stack->top = NULL;
		ret = STACK_LINKED_OK;
	}
	return ret;
}


StackReturn_t StackLinkedEmpty(StackLinked_t* _stack)
{
	StackReturn_t ret = STACK_LINKED_OK;
	if (NULL == _stack)
	{
		ret = STACK_LINKED_NULL;
	}
	else
	{
		if (NULL == _stack->top)
		{
			ret = STACK_LINKED_EMPTY;
		}
		else { /* Nothing */ }
	}
	return ret;
}


StackReturn_t StackLinkedPush(StackLinked_t* _stack, StackEntry_t  _entry)
{
	StackReturn_t ret = STACK_LINKED_OK;
	if (NULL == _stack)
	{
		ret = STACK_LINKED_NULL;
	}
	else
	{
		StackNode_t* newNode = createNode(_entry);
		newNode->next = _stack->top;
		_stack->top = newNode;
		ret = STACK_LINKED_OK;
	}
	return ret;
}


StackReturn_t StackLinkedPop(StackLinked_t* _stack, StackEntry_t* _entry)
{
	StackReturn_t ret = STACK_LINKED_OK;
	if (NULL == _stack)
	{
		ret = STACK_LINKED_NULL;
	}
	else if (STACK_LINKED_EMPTY == StackLinkedEmpty(_stack))
	{
		ret = STACK_LINKED_EMPTY;
	}
	else
	{
		StackNode_t* node = _stack->top;
		_entry = node->entry;
		_stack->top = node->next;
		free(node);
		ret = STACK_LINKED_OK;
	}
	return ret;
}


StackReturn_t StackLinkedTop(StackLinked_t* _stack, StackEntry_t* _entry)
{
	StackReturn_t ret = STACK_LINKED_OK;
	if (NULL == _stack)
	{
		ret = STACK_LINKED_NULL;
	}
	else if (STACK_LINKED_EMPTY == StackLinkedEmpty(_stack))
	{
		ret = STACK_LINKED_EMPTY;
	}
	else
	{
		*_entry = _stack->top->entry;
		ret = STACK_LINKED_OK;
	}
	return ret;
}


StackReturn_t StackLinkedSize(StackLinked_t* _stack, int* _size)
{
	StackReturn_t ret = STACK_LINKED_OK;
	if (NULL == _stack)
	{
		ret = STACK_LINKED_NULL;
	}
	else
	{
		StackNode_t* node = _stack->top;
		for (*_size = 0; node != NULL; node = node->next) (*_size)++;
		ret = STACK_LINKED_OK;
	}
	return ret;
}


StackReturn_t StackLinkedClear(StackLinked_t* _stack)
{
	StackReturn_t ret = STACK_LINKED_OK;
	if (NULL == _stack)
	{
		ret = STACK_LINKED_NULL;
	}
	else
	{
		StackNode_t* node = _stack->top;
		while (node != NULL)
		{
			node = node->next;
			free(_stack->top);
			_stack->top = node;
		}
		ret = STACK_LINKED_OK;
	}
	return ret;
}


StackReturn_t StackLinkedDisplay(StackLinked_t* _stack)
{
	StackReturn_t ret = STACK_LINKED_OK;
	if (NULL == _stack)
	{
		ret = STACK_LINKED_NULL;
	}
	else if (STACK_LINKED_EMPTY == StackLinkedEmpty(_stack))
	{
		ret = STACK_LINKED_EMPTY;
	}
	else
	{
		printf("\nStack Display\n[ ");
		StackNode_t* node = _stack->top;
		while (node != NULL)
		{
			printf(" %s ", node->entry);
			node = node->next;
		}
		printf(" ]\n");
		ret = STACK_LINKED_OK;
		
	}
	return ret;
}


StackReturn_t StackLinkedTraverse(StackLinked_t* _stack, void (*pvisit)(StackEntry_t))
{
	StackReturn_t ret = STACK_LINKED_OK;
	if (NULL == _stack)
	{
		ret = STACK_LINKED_NULL;
	}
	else if (STACK_LINKED_EMPTY == StackLinkedEmpty(_stack))
	{
		ret = STACK_LINKED_EMPTY;
	}
	else
	{
		StackNode_t* node = _stack->top;
		for (node; node != NULL; node = node->next)
		{
			(*pvisit)(node->entry);
		}
		ret = STACK_LINKED_OK;
	}
	return ret;
}


static StackNode_t* createNode(StackEntry_t _entry)
{
	StackNode_t* newNode = (StackNode_t*)malloc(sizeof(StackNode_t));
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
