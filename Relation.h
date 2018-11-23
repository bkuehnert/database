#ifndef _RELATION_H
#define _RELATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "HashTable.h"

typedef struct Relation 
{
	char** names;
	int size;
	int primary_hash;
	int* secondary_hash;
	HashTable* primary;
	HashTable** secondary;
} Relation;

Relation* create_Relation(int size, int primary_hash, int* secondary_hash, char** names);

bool rel_equalSchema(Relation* r1, Relation* r2);

Relation* project(Relation* r1, bool* columns);

Relation* selection(Relation* r, bool notq, int column, char* string);

void rel_insert(Relation* r, Tuple* t);

void rel_insertSet(Relation* r, TupleSet* t);

TupleSet* rel_query(Relation* r, Tuple* t);

void rel_delete(Relation* r, Tuple* t);

#endif
