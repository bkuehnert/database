#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LongLinkedListSetNode
{
	void* tag;
	struct LongLinkedListSetNode* next;
} Node;

typedef struct Set
{
	struct LongLinkedListSetNode* first;
	struct LongLinkedListSetNode* last;
	int size;
} Set;

void add(Set* list, void* add)
{
	if(list->size == 0)
	{
		Node* toAdd = (Node*)calloc(1, sizeof(Node));
		toAdd->tag = add;
		list->first = toAdd;
		list->last = toAdd;
		list->size = 1;
	}
	else
	{
		for(Node* check = list->first; check!=0; check=check->next)
		{
			if(check->tag == add)
				return;
		}

		Node* toAdd = (Node*)calloc(1, sizeof(Node));
		toAdd->tag = add;
		list->last->next = toAdd;
		list->last = toAdd;
		list->size++;
	}
}

int indexOf(Set* list, void* checkLong)
{
	int i = 0;

	for(Node* check = list->first; check!=0; check=check->next)
	{
		if(check->tag == checkLong)
			return i;

		i++;
	}

	return -1;
}

void freeList(Set* list)
{
	Node* cur = list->first;

	while(cur)
	{
		Node* next = cur->next;
		free(cur);
		cur = next;
	}
}

#endif
