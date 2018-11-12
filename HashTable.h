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
	int count;
} HashTable;

HashTable* create_HashTable(int* key_vector);

void ht_put(HashTable* h, Tuple* t);

//should make this a hashmap itself
Set* ht_get(Tuple* t);


#endif
