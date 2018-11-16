#include "Relation.h"

Relation* create_Relation(int size, int primary_hash, int* secondary_hash, char** names)
{
	Relation* ret = (Relation*)malloc(sizeof(Relation));
	ret->names = names;
	ret->size = size;
	ret->primary_hash = primary_hash;
	ret->secondary_hash = secondary_hash;
	ret->primary = create_HashTable(primary_hash);
	ret->secondary = (HashTable**)malloc(size*sizeof(HashTable*));
	for(int i = 0; i<size; i++) {
		if(secondary_hash[i]) ret->secondary[i] = create_HashTable(i);
		else ret->secondary[i] = NULL;
	}
	return ret;
}

