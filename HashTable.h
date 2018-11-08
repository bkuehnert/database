#ifndef HASHSET_H
#define HASHSET_H

#include "Tuple.h"
#include "Set.h"

typedef struct ht_Node 
{
	struct ht_Node* next;
	Tuple* data;
} ht_Node;

typedef struct HashTable 
{
	struct ht_Node** buckets;		
	int* key_vector;
	int size;
	int count;
} HashTable;

void ht_put(Tuple t);

//should make this a hashmap itself
Set ht_get(Tuple t);


#endif
