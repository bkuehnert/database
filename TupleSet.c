#include "TupleSet.h"
#include "Tuple.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void addAllNodes(Node* in, TupleSet* copy);

int tupleEql(Tuple* a, Tuple* b)
{
	if(a->n != b->n)
		return 0;

	for(int i = 0; i < a->n; i++)
	{
		if(strcmp(a->data[i], b->data[i]))
			return 0;
	}

	return 1;
}

TupleSet* createSet()
{
	TupleSet* set = (TupleSet*) calloc(sizeof(TupleSet), 1);
	set->buckets = (Node**)calloc(sizeof(Node*), 1009);
	set->size = 0;
	return set;
}

int setHash(Tuple* tuple)
{
	int hash = 0;

	for(int i = 0; i < tuple->n; i++)
	{
		for(int j = 0; tuple->data[i][j]!=0; j++)
		{
			hash+=tuple->data[i][j];
		}
	}

	return hash%1009;
}

void add(TupleSet* list, Tuple* add)
{
	int hash = setHash(add);
	Node* toAdd = list->buckets[hash];

	if(toAdd == 0)
	{
		Node* new = malloc(sizeof(Node));
		new->data = add;
		new->next = 0;
		list->buckets[hash] = new;
		list->size++;
	}
	else
	{
		while(toAdd->next != 0)
		{
			if(tupleEql(toAdd->data, add))
				return;

			toAdd = toAdd->next;
		}

		if(tupleEql(toAdd->data, add))
			return;

		Node* new = malloc(sizeof(Node));
		new->data = add;
		new->next = 0;
		toAdd->next = new;
		list->size++;
	}
}

int contains(TupleSet* list, Tuple* checkTuple)
{
	int hash = setHash(checkTuple);
	Node* bucket = list->buckets[hash];

	while(bucket!=0)
	{
		if(tupleEql(bucket->data,checkTuple))
			return 1;

		bucket=bucket->next;
	}

	return 0;
}

void freeNode(Node* node)
{
	if(node->next!=0)
		freeNode(node->next);

	free(node);
}

void freeList(TupleSet* list)
{
	for(int i = 0; i < 1009; i++)
	{
		if(list->buckets[i]!=0)
		{
			freeNode(list->buckets[i]);
		}
	}

	free(list->buckets);
	free(list);
}

void addAll(TupleSet* in, TupleSet* copy)
{
	for(int i = 0; i < 1009; i++)
	{
		Node* node = in->buckets[i];
		addAllNodes(node, copy);
	}
}

void intersectAllNodes(Node* in, TupleSet* copy, TupleSet* compare)
{
	if(in == 0)
		return;

	if(contains(compare, in->data))
	{
		add(copy, in->data);
	}

	intersectAllNodes(in->next, copy, compare);
}

TupleSet* intersection(TupleSet* a, TupleSet* b)
{
	TupleSet* c = createSet();

	for(int i = 0; i < 1009; i++)
	{
		Node* node = b->buckets[i];
		intersectAllNodes(node, c, a);
	}

	return c;
}

void addAllNodes(Node* in, TupleSet* copy)
{
	if(in == 0)
		return;

	add(copy, in->data);
	addAllNodes(in->next, copy);
}

TupleSet* join(TupleSet* a, TupleSet * b)
{
	TupleSet* c = createSet();
	addAll(a,c);
	addAll(b,c);
	return c;
}

void printNode(Node* node)
{
	if(node==0)
		return;

	printf("(");
	printTuple(node->data);
	printf(")");
	printNode(node->next);
}

void print(TupleSet* set)
{
	printf("{");

	for(int i = 0; i < 1009; i++)
	{
		Node* node = set->buckets[i];
		printNode(node);
	}

	printf("}");
}

int tryRemove(Tuple* remove, Node* prev, Node* cur)
{
	if(cur == 0)
		return 0;

	if(tupleEql(remove, cur->data))
	{
		prev->next = cur->next;
		free(cur);
		return 1;
	}

	return tryRemove(remove, cur, cur->next);
}

void removeSet(TupleSet* set, Tuple* remove)
{
	for(int i = 0; i < 1009; i++)
	{
		Node* node = set->buckets[i];

		if(node!=0)
		{
			if(tupleEql(node->data, remove))
			{
				set->buckets[i] = node->next;
				free(node);
				set->size--;
			}
			else if((node->next!=0) & (tryRemove(remove, node, node->next)))
			{
				set->size--;
			}
		}
	}
}
