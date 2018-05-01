//LinkedList.c
#include "LinkedList.h"
#include <stdlib.h>
#include <memory.h>

void LinkedList_Create(LinkedList *linkedList) {
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->current = NULL;
}
Node* LinkedList_InsertBefore(LinkedList *linkedList, Node *index, void *object, size_t size)
{
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->next = index;
	if (linkedList->head != index)
	{
		linkedList->current->next = index->previous;
		index->previous->next = linkedList->current;
	}
	else
	{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	index->previous = linkedList->current;
	linkedList->length++;
	return linkedList->current;
}
Node* LinkedList_InsertAfter(LinkedList *linkedList, Node *index, void *object, size_t size)
{
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->previous = index;
	if (linkedList->tail != index)
	{
		linkedList->current->next = index->next;
		index->next->previous = linkedList->current;
	}
	else
	{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	index->next = linkedList->current;
	linkedList->length++;
	return linkedList->current;
}
Node* LinkedList_AppendFromHead(LinkedList *linkedList, void *object, size_t size)
{
	linkedList->current= (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->previous = linkedList->current;
	if (linkedList->head != NULL)
	{
		linkedList->current->next = linkedList->head;
		linkedList->head->previous = linkedList->current;
	}
	else
	{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	linkedList->head = linkedList->current;
	linkedList->length++;
	return linkedList->current;
}
Node* LinkedList_AppendFromTail(LinkedList *linkedList, void *object, size_t size)
{
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->next = linkedList->current;
	if (linkedList->head != NULL)
	{
		linkedList->current->previous = linkedList->tail;
		linkedList->tail->next = linkedList->current;
	}
	else
	{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	linkedList->tail = linkedList->current;
	linkedList->length++;
	return linkedList->current;
}

void LinkedList_DeleteAllItems(LinkedList *linkedList)
{
	Node *previous = NULL;
	Node *it;
	it = linkedList->head;
	while (it != previous)
	{
		previous = it;
		linkedList->head = linkedList->head->next;
		if (it != NULL)
		{
			free(it);
		}
		linkedList->length--;
		it = linkedList->head;
	}
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->current = NULL;
}
Node* LinkedList_Delete(LinkedList *linkedList, Node *index)
{
	if (linkedList->tail != index)
	{
		linkedList->current = index->next;
	}
	else
	{
		linkedList->current = index->previous;
	}
	if (linkedList->head != index&&linkedList->tail != index)
	{
		index->previous->next = index->next;
		index->next->previous = index->previous;
	}
	else if (linkedList->head == linkedList->tail)
	{
		linkedList->head = NULL;
		linkedList->current = NULL;
		linkedList->tail = NULL;
	}
	else if (linkedList->tail == index)
	{
		index->previous->next = index->previous;
		linkedList->tail = index->previous;
	}
	else
	{
		index->next->previous = index->next;
		linkedList->head = index->next;
	}
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	linkedList->length--;
	return index;
}

Node* LinkedList_DeleteFromHead(LinkedList *linkedList)
{
	Node *index;
	index = linkedList->head;
	if (linkedList->head != linkedList->tail)
	{
		linkedList->current = linkedList->head->next;
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	linkedList->length--;
	return index;
}
Node* LinkedList_DeleteFromTail(LinkedList *linkedList)
{
	Node *index;
	index = linkedList->tail;
	if (linkedList->head != linkedList->tail)
	{
		linkedList->current = linkedList->tail->previous;
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
		else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	linkedList->length--;
	return index;
}
Node* LinkedList_LinearSearchUnique(LinkedList *linkedList, void *key, int(*compare)(void *, void*))
{
	Node* index = NULL;
	Node* previous = NULL;
	Node *it;
	it = linkedList->head;
	while (it != previous&&compare(it + 1, key) != 0)
	{
		previous = it;
		it = it->next;

	}
	if (it != previous)
	{
		index = it;
	}
	return index;
}
void LinkedList_LinearSearchDuplicate(LinkedList *linkedList, void *key, Long *count, Node **(*indexes),  int(*compare)(void *, void*))
{
	Node * previous = NULL;
	Node * it;
	Long i = 0;
	*count = 0;
	*indexes = (Node*(*))calloc(linkedList->length, sizeof(Node*));
	it = linkedList->head;
	while (it != previous)
	{
		if (compare(it + 1, key) == 0)
		{
			(*indexes)[i] = it;
			i++;
			(*count)++;
		}
		previous = it;
		it = it->next;
	}
}


Node* LinkedList_First(LinkedList *linkedList)
{
	linkedList->current = linkedList->head;
	return linkedList->current;
}

Node* LinkedList_Previous(LinkedList *linkedList)
{
	linkedList->current = linkedList->current->previous;
	return linkedList->current;
}
Node* LinkedList_Next(LinkedList *linkedList)
{
	linkedList->current = linkedList->current->next;
	return linkedList->current;
}
Node* LinkedList_Last(LinkedList *linkedList)
{
	linkedList->current = linkedList->tail;
	return linkedList->current;
}

void LinkedList_GetAt(LinkedList *linkedList, Node *index, void *object, size_t size) //index 받아서 object 뽑아내기
{
	memcpy(object, index + 1, size); // object 에다가 index + 1 부터 size 크기만큼의 메모리를 저장한다
}

void LinkedList_Destroy(LinkedList *linkedList)
{
	Node *previous = NULL;
	Node *current;
	current = linkedList->head;
	while (previous != current)
	{
		linkedList->head = current->next;
		previous = current;
		if (current != NULL)
		{
			free(current);
		}
		current = linkedList->head;
	}
}
