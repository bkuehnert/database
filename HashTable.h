#ifndef _h_hashset
#define _h_hashset

#include "Tuple.h"

typedef struct Node 
{
	struct Node* next;
	Tuple* data;
} Node;

typedef struct HashTable 
{
	struct Node** buckets;		
	int size;
	int count;
} HashTable;


#endif
