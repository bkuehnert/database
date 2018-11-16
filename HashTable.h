#ifndef HASHSET_H
#define HASHSET_H

#include "Tuple.h"
#include "TupleSet.h"

typedef struct ht_Node 
{
	struct ht_Node* next;
	Tuple* data;
} ht_Node;

typedef struct HashTable 
{
	struct ht_Node** buckets;		
	int key;
	int count;
} HashTable;

HashTable* create_HashTable(int key);

void ht_put(HashTable* h, Tuple* t);

//should make this a hashmap itself
TupleSet* ht_get(HashTable* h, char* key);



#endif
