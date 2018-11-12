#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tuple.h"

typedef struct SetNode
{
	struct SetNode* left;
	struct SetNode* right;
	struct SetNode* in;
	Tuple* data;
	long hash;
} Node;

typedef struct TupleSet
{
	Node* head;
	int size;
} TupleSet;

TupleSet* createSet();

void add(TupleSet* list, Tuple* add);

int contains(TupleSet* list, Tuple* checkTuple);

void freeList(TupleSet* list);

TupleSet* intersection(TupleSet* a, TupleSet * b);

TupleSet* join(TupleSet* a, TupleSet * b);

void print(TupleSet* set);

#endif
