#include "TupleSet.h"
#include "Tuple.h"
#include <string.h>

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
	TupleSet* set = (TupleSet*) calloc(sizeof(TupleSet*), 1);
	set->head = 0;
	set->size = 0;
	return set;
}

long setHash(Tuple* tuple)
{
	long hash = 0;

	for(int i = 0; i < tuple->n; i++)
	{
		for(int j = 0; tuple->data[i][j]!=0; j++)
		{
			hash+=tuple->data[i][j];
		}
	}

	return hash;
}

void addSet(Node* list, Node* add, long hash)
{
	if(list->hash > hash)
	{
		if(list->left == 0)
		{
			list->left = add;
		}
		else
		{
			addSet(list->left, add, hash);
		}
	}
	else if(list->hash < hash)
	{
		if(list->right == 0)
		{
			list->right = add;
		}
		else
		{
			addSet(list->right, add, hash);
		}
	}
	else
	{
		Node* cur = list;

		while(cur!=0)
		{
			if(tupleEql(add->data, cur->data))
				return;

			if(cur->in != 0)
				cur=cur->in;
			else
			{
				cur->in = add;
				return;
			}
		}

		return;
	}
}

void add(TupleSet* list, Tuple* add)
{
	long val = setHash(add);
	Node* node = calloc(sizeof(Node), 1);
	node->hash = val;
	node->data = add;
	node->in = 0;
	node->left = 0;
	node->right = 0;

	if(list->size == 0)
		list->head = node;
	else
		addSet(list->head, node, val);

	list->size++;
}

int containHelper(Node* head, Tuple* tup, long hash)
{
	if(head->hash == hash)
	{
		Node* cur = head;

		while(cur!=0)
		{
			if(tupleEql(tup, cur->data))
				return 1;

			cur=cur->in;
		}

		return 0;
	}

	if(head->hash>hash)
	{
		if(head->left == 0)
			return 0;

		return containHelper(head->left, tup, hash);
	}

	if(head->right == 0)
		return 0;

	return containHelper(head->right, tup, hash);
}


int contains(TupleSet* list, Tuple* checkTuple)
{
	long hash = setHash(checkTuple);
	return containHelper(list->head, checkTuple, hash);
}

void freeHelper(Node* list)
{
	if(list == 0)
		return;

	freeHelper(list->in);
	freeHelper(list->left);
	freeHelper(list->right);
	free(list);
}

void freeList(TupleSet* list)
{
	freeHelper(list->head);
	free(list);
}

TupleSet* intersection(TupleSet* a, TupleSet * b);

void printHelper(Node* list)
{
	if(list == 0)
		return;

	printTuple(list->data);

	printHelper(list->in);
	printHelper(list->left);
	printHelper(list->right);
}

void print(TupleSet* set)
{
	printHelper(set->head);
}
