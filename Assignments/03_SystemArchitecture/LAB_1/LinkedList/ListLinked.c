#include "ListLinked.h"

ListLinkedReturn_t ListLinkedInit(ListLinked_t* _list)
{
	ListLinkedReturn_t ret = LIST_LINKED_OK;
	if (NULL == _list)
	{
		ret = LIST_LINKED_NULL;
	}
	else
	{
		_list->head = NULL;
		_list->size = 0;
		ret = LIST_LINKED_OK;
	}
	return ret;
}


ListLinkedReturn_t ListLinkedEmpty(ListLinked_t* _list)
{
	ListLinkedReturn_t ret = LIST_LINKED_OK;
	if (NULL == _list)
	{
		ret = LIST_LINKED_NULL;
	}
	else
	{
		if(0 == _list -> size)
		{
			ret = LIST_LINKED_EMPTY;
		}
		else { /* Nothing */ }
	}
	return ret;
}


ListLinkedReturn_t ListLinkedSize(ListLinked_t* _list, int* _size)
{
	ListLinkedReturn_t ret = LIST_LINKED_OK;
	if (NULL == _list)
	{
		ret = LIST_LINKED_NULL;
	}
	else if (0 == _list->size)
	{
		ret = LIST_LINKED_EMPTY;
	}
	else
	{
		*_size = _list->size;
		ret = LIST_LINKED_OK;
	}
	return ret;
}


ListLinkedReturn_t ListLinkedClear(ListLinked_t* _list)
{
	ListLinkedReturn_t ret = LIST_LINKED_OK;
	if (NULL == _list)
	{
		ret = LIST_LINKED_NULL;
	}
	else if (0 == _list->size)
	{
		ret = LIST_LINKED_EMPTY;
	}
	else
	{
		ListNode_t* _node;
		while (_list->head)
		{
			_node = _list->head->next;
			free(_list->head);
			_list->head = _node;
		}
		_list->size = 0;
		ret = LIST_LINKED_OK;
	}
	return ret;
}


ListLinkedReturn_t ListLinkedDisplay(ListLinked_t* _list)
{
	ListLinkedReturn_t ret = LIST_LINKED_OK;
	if (NULL == _list)
	{
		ret = LIST_LINKED_NULL;
	}
	else if (0 == _list->size)
	{
		ret = LIST_LINKED_EMPTY;
	}
	else
	{
		printf("\nQueue Display\n[ ");
		ListNode_t* _node = _list->head;
		while (_node)
		{
			printf(" %d ", _node->entry);
			_node = _node->next;
		}
		printf(" ]\n");
		ret = LIST_LINKED_OK;
	}
	return ret;
}


ListLinkedReturn_t ListLinkedTraverse(ListLinked_t* _list, void (*pvisit)(ListLinkedEntry_t))
{
	ListLinkedReturn_t ret = LIST_LINKED_OK;
	if (NULL == _list)
	{
		ret = LIST_LINKED_NULL;
	}
	else if (0 == _list->size)
	{
		ret = LIST_LINKED_EMPTY;
	}
	else
	{
		ListNode_t* _node = _list->head;
		while (_node)
		{
			(*pvisit)(_node->entry);
			_node = _node->next;
		}
		ret = LIST_LINKED_OK;
	}
	return ret;
}