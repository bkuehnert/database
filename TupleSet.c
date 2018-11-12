#include "TupleSet.h"
#include "Tuple.h"


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

void add(TupleSet* list, Tuple* add)
{
	long val = setHash(add);
	Node* node = calloc(sizeof(Node), 1);
	node->hash = val;
	node->in = 0;
	node->left = 0;
	node->right = 0;

	if(list->size == 0)
		list->head = node;
	else

}

int indexOf(TupleSet* list, Tuple* checkTuple);

void freeList(TupleSet* list);

TupleSet* intersection(TupleSet* a, TupleSet * b);
