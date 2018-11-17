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

void rel_insert(Relation* r, Tuple* t)
{
	if( r->size != t->n ) return;

	ht_put(r->primary, t);
	for(int i = 0; i<r->size; i++)
		if(r->secondary_hash[i]) ht_put(r->secondary[i], t);
}

void setMatchHelper(TupleSet* set, int index, char* key, Node* node)
{
	if(node == 0)
		return;

	if(strcmp(key, node->data->data[index])!=0)
	{
		removeSet(set, node->data);
	}

	setMatchHelper(set, index, key, node->next);
}

void setMatch(TupleSet* set, int index, char* key)
{
	for(int i = 0; i < 1009; i++)
	{
		if(set->buckets[i]!=0)
			setMatchHelper(set, index, key, set->buckets[i]);
	}
}

TupleSet* rel_query(Relation* r, Tuple* t)
{
	if(r->size != t->n)
		return 0;

	TupleSet* set;

	int primary = r->primary_hash;
	HashTable* primaryTable = r->primary;

	if(strcmp(t->data[primary], "*")==0)
	{
		set = ht_getAll(primaryTable);
	}
	else
	{
		set = ht_get(primaryTable, t->data[primary]);
	}

	for(int i = 0; i < r->size; i++)
	{
		if(i!=primary)
		{
			if(strcmp(t->data[i], "*")==0)
				continue;

			if(r->secondary_hash[i])
			{
				TupleSet* newPull = ht_get(r->secondary[i], t->data[i]);
				TupleSet* intersect = intersection(set, newPull);
				freeList(set);
				freeList(newPull);
				set = intersect;
			}
			else
			{
				setMatch(set, i, t->data[i]);
			}
		}
	}

	return set;
}
