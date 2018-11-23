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
} HashTable;

HashTable* create_HashTable(int key);

void htnodeFree(ht_Node* n);

int hash_string(char* string);

void ht_put(HashTable* h, Tuple* t);

TupleSet* ht_get(HashTable* h, char* key);

TupleSet* ht_getAll(HashTable* h);

void ht_remove(HashTable* h, Tuple* t);

void ht_addSet(HashTable* h, TupleSet* set);

#endif
