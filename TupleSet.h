#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tuple.h"

typedef struct SetNode
{
	struct SetNode* next;
	Tuple* data;
} Node;

typedef struct TupleSet
{
	Node** buckets;
	int size;
} TupleSet;

TupleSet* createSet();

void add(TupleSet* list, Tuple* add);

int contains(TupleSet* list, Tuple* checkTuple);

void freeList(TupleSet* list);

TupleSet* intersection(TupleSet* a, TupleSet * b);

TupleSet* join(TupleSet* a, TupleSet * b);

void print(TupleSet* set);

void removeSet(TupleSet* set, Tuple* remove);

Tuple* get(int index);

#endif
