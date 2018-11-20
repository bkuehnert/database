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

void rel_delete(Relation* r, Tuple* t)
{
	if(r->size != t->n) return;

	ht_remove(r->primary, t);

	for(int i = 0; i < r->size; i++)
	{
		if(r->secondary_hash[i]) ht_remove(r->secondary[i], t);
	}
}

Relation* project(Relation* r1, int* columns)
{
	char* searchArray[r1->size];
	int newCols = 0;

	for(int i = 0; i < r1->size; i++)
	{
		searchArray[i] = "*";

		if(columns[i])
		{
			newCols++;
		}
	}

	int* newHashSecondaries = calloc(sizeof(int), newCols);

	int curSecHashInsert = 0;
	int primaryHash = -1;

	for(int i = 0; i < r1->size; i++)
	{
		if(columns[i] & r1->secondary_hash[i])
		{
			if(primaryHash == -1)
				primaryHash = newHashSecondaries[curSecHashInsert++];
			else
				newHashSecondaries[curSecHashInsert++] = 1;
		}
		else if(i == r1->primary_hash)
		{
			if(primaryHash == -1)
				primaryHash = newHashSecondaries[curSecHashInsert++];
			else
				newHashSecondaries[curSecHashInsert++] = 1;
		}
	}

	Tuple* queryAll = create_Tuple(r1->size, searchArray);
	TupleSet* set = rel_query(r1, queryAll);

	Relation* newRelation = create_Relation(newCols, primaryHash == -1 ? 0 : primaryHash, newHashSecondaries, 0);

	for(int i = 0; i < 1009; i++)
	{
		Node* bucket = set->buckets[i];

		while(bucket!=0)
		{
			char** newData = malloc(sizeof(char*) * newCols);
			Tuple* original = bucket->data;
			int curInsert = 0;

			for(int i = 0; i < r1->size; i++)
			{
				if(columns[i])
				{
					newData[curInsert++] = original->data[i];
				}
			}

			Tuple* modified = create_Tuple(newCols, newData);
			rel_insert(newRelation, modified);
			bucket=bucket->next;
		}
	}

	freeList(set);
	free(queryAll);
	return newRelation;
}
