#ifndef __LIST_LINKED_H__
#define __LIST_LINKED_H__

#include <stdio.h>
#include <stdlib.h>

typedef void* ListLinkedEntry_t;

typedef struct node
{
	ListLinkedEntry_t entry;
	struct node* next;
}ListNode_t;

typedef struct list
{
	ListNode_t *head;
	int size;
}ListLinked_t;

typedef enum
{
	LIST_LINKED_OK = 0,
	LIST_LINKED_NULL,
	LIST_LINKED_FULL,
	LIST_LINKED_EMPTY,
	LIST_LINKED_NOT_INTIALIZED
}ListLinkedReturn_t;

ListLinkedReturn_t ListLinkedInit(ListLinked_t* _list);
ListLinkedReturn_t ListLinkedEmpty(ListLinked_t* _list);
					   
ListLinkedReturn_t ListLinkedInsert(ListLinked_t* _list, ListLinkedEntry_t  _entry, int _index);
ListLinkedReturn_t ListLinkedRetrieve(ListLinked_t* _list, ListLinkedEntry_t* _entry, int _index);
ListLinkedReturn_t ListLinkedDelete(ListLinked_t* _list, ListLinkedEntry_t* _entry, int _index);
ListLinkedReturn_t ListLinkedReplace(ListLinked_t* _list, ListLinkedEntry_t* _entry, int _index);
					   
ListLinkedReturn_t ListLinkedSize(ListLinked_t* _list, int* _size);
ListLinkedReturn_t ListLinkedClear(ListLinked_t* _list);
ListLinkedReturn_t ListLinkedDisplay(ListLinked_t* _list);
ListLinkedReturn_t ListLinkedTraverse(ListLinked_t* _list, void (*pvisit)(ListLinkedEntry_t));

#endif // !__LIST_LINKED_H__
