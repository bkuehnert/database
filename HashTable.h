#ifndef _h_hashset
#define _h_hashset

#include "Tuple.h"

struct Node {
	struct Node* next;
	Tuple* data;
};

struct HashTable {
	struct Node** buckets;		
	int size;
	int count;
};

typedef struct Node Node;
typedef struct HashTable HashTable;

#endif
