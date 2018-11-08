#ifndef HASHSET_H
#define HASHSET_H

#include "Tuple.h"
#include "Set.h"

typedef struct Node 
{
	struct Node* next;
	Tuple* data;
} Node;

typedef struct HashTable 
{
	struct Node** buckets;		
	int* key_vector;
	int size;
	int count;
} HashTable;

void ht_put(Tuple t);

Set ht_get(Tuple t);


#endif
