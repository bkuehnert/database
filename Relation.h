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


#endif
