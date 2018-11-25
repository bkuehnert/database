#include "Relation.h"
#include <stdio.h>

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

void rel_insertSet(Relation* r, TupleSet* set)
{

	ht_addSet(r->primary, set);
	for(int i = 0; i<r->size; i++)
		if(r->secondary_hash[i]) ht_addSet(r->secondary[i], set);
}

void setMatchHelper(TupleSet* set, int index, char* key, Node* node)
{
	if(node == 0)
		return;

	if(strcmp(key, node->data->data[index])!=0)
	{
		removeSet(set, node->data);
	}
	else
	{
		setMatchHelper(set, index, key, node->next);
	}
	
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

Relation* selection(Relation* r, bool notq, int column, char* string)
{
	Relation* ret = create_Relation(r->size, r->primary_hash, r->secondary_hash, r->names);
	if(!notq) {
		if(r->secondary_hash[column]) {
			for(ht_Node* bucket = r->secondary[column]->buckets[hash_string(string)]; bucket != NULL; bucket = bucket->next)
			rel_insert(ret, bucket->data);				
		}
		else if(r->primary_hash == column){
			for(ht_Node* bucket = r->primary->buckets[hash_string(string)]; bucket != NULL; bucket = bucket->next)
			rel_insert(ret, bucket->data);				
		}
		else {
			for(int i = 0; i < 1009; i++) {
				for(ht_Node* bucket = r->primary->buckets[i]; bucket != NULL; bucket = bucket->next) {
					if(strcmp(bucket->data->data[column], string) == 0)
						rel_insert(ret, bucket->data);
				}
			}
		}
	}
	else {
		printf("todo\n");
	}
	return ret;
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
	char** newNames = calloc(sizeof(char*), newCols);

	int curSecHashInsert = 0;
	int primaryHash = -1;
	int nameIndex = 0;

	for(int i = 0; i < r1->size; i++)
	{
		if(columns[i] & r1->secondary_hash[i])
		{
			if(primaryHash == -1)
				primaryHash = newHashSecondaries[curSecHashInsert++];
			else
				newHashSecondaries[curSecHashInsert++] = 1;

			newNames[nameIndex] = r1->names[i];
			nameIndex++;
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

	Relation* newRelation = create_Relation(newCols, primaryHash == -1 ? 0 : primaryHash, newHashSecondaries, newNames);

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

Relation* joinRelation(Relation* r1, Relation* r2, int col1, int col2)
{
	int* secondaryHashes = calloc(sizeof(int), r1->size+r2->size-1);
	char** newNames = calloc(sizeof(char*), r1->size+r2->size-1);

	for(int i = 0; i < r1->size; i++)
	{
		secondaryHashes[i] = r1->secondary_hash[i];
		newNames[i] = r1->names[i];
	}

	for(int i = 0; i < col2; i++)
	{
		secondaryHashes[i+r1->size] = r2->secondary_hash[i];
		newNames[i+r1->size] = r2->names[i];
	}

	for(int i = col2+1; i < r2->size; i++)
	{
		secondaryHashes[i+r1->size-1] = r2->secondary_hash[i];
		newNames[i+r1->size-1] = r2->names[i];
	}

	Relation* newRelation = create_Relation(r1->size+r2->size-1, r1->primary_hash, secondaryHashes, newNames);

	for(int i = 0; i < 1009; i++)
	{
		ht_Node* head1 = r1->primary->buckets[i];

		while(head1!=0)
		{
			Tuple* tuple1 = head1->data;

			for(int j = 0; j < 1009; j++)
			{
				ht_Node* head2 = r2->primary->buckets[j];

				while(head2!=0)
				{
					Tuple* tuple2 = head2->data;

					if(!strcmp(tuple1->data[col1], tuple2->data[col2]))
					{
						char** newData = calloc(sizeof(char*), r1->size+r2->size-1);

						for(int i = 0; i < r1->size; i++)
						{
							newData[i] = tuple1->data[i];
						}

						for(int i = 0; i < col2; i++)
						{
							newData[i+r1->size] = tuple2->data[i];
						}

						for(int i = col2+1; i < r2->size; i++)
						{
							newData[i+r1->size-1] = tuple2->data[i];
						}

						rel_insert(newRelation, create_Tuple(r1->size+r2->size-1, newData));
					}

					head2 = head2->next;
				}
			}

			head1=head1->next;
		}
	}

	return newRelation;
}

void saveRel(Relation* rel, char* name)
{
	FILE* saveFile = fopen(name, "w");
	fprintf(saveFile, "%d %d", rel->primary_hash, rel->size);

	for(int i = 0; i < rel->size; i++)
	{
		fprintf(saveFile, "\n%s %c", rel->names[i], rel->secondary_hash[i] ? '1' : '0');
	}

	for(int i = 0; i < 1009; i++)
	{
		ht_Node* bucket = rel->primary->buckets[i];

		while(bucket!=0)
		{
			Tuple* toWrite = bucket->data;
			bucket=bucket->next;
			fprintf(saveFile, "\n");

			for(int i = 0; i < toWrite->n; i++)
			{
				if(i == toWrite->n-1) fprintf(saveFile, "%s", toWrite->data[i]);
				else fprintf(saveFile, "%s ", toWrite->data[i]);
			}
		}
	}

	fclose(saveFile);
}

Tuple* readTuple(FILE* saveFile, int size)
{
	char** newDataString = calloc(sizeof(char*), size);

	for(int i = 0; i < size; i++)
	{
		char* data = calloc(sizeof(char*), size);
		int read = fscanf(saveFile, "%s", data);

		if(read == EOF)
		{
			free(data);

			for(int j = 0; j < i; j++)
			{
				free(newDataString[j]);
			}

			free(newDataString);
			return 0;
		}
		else
			newDataString[i] = data;
	}

	return create_Tuple(size, newDataString);
}

Relation* loadRel(char* name)
{
	FILE* saveFile = fopen(name, "r");
	int size = 0;
	int primary = 0;
	fscanf(saveFile, "%d%d", &primary, &size);
	char** newNames = calloc(sizeof(char*), size);
	int* secondaryHashes = calloc(sizeof(int), size);

	for(int i = 0; i < size; i++)
	{
		char* attribute = calloc(sizeof(char), 50);
		int value = 0;
		fscanf(saveFile, "%s%d", attribute, &value);
		newNames[i] = attribute;
		secondaryHashes[i] = 50;
	}

	Relation* newRel = create_Relation(size, primary, secondaryHashes, newNames);

	while(1)
	{
		Tuple* read = readTuple(saveFile, size);

		if(read == 0)
			break;
		else
			rel_insert(newRel, read);
	}

	fclose(saveFile);
	return newRel;
}

void printRel(Relation* r)
{
	
	for(int i = 0; i < r->size; i++) {
		if(i == r->size-1) printf("%s\n", r->names[i]);
		else printf("%s\t",r->names[i]);
	}
	
	for(int i = 0; i < 1009; i++) {
		for(ht_Node* ptr = r->primary->buckets[i]; ptr != NULL; ptr = ptr->next) {
			printTuple(ptr->data);
			printf("\n");
		}
	}
	printf("\n");
}
