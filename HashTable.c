#include "HashTable.h"
#include <stdlib.h>
#include <string.h>

int sum_bytes(char* string)
{
	int sum = 0;
	for(int i = 0; i < strlen(string); i++) {
		sum += string[i];
	}
	return sum;
}

int hash(const int key, Tuple* t)
{
	return sum_bytes(t->data[key]) % 1009;
}

ht_Node* create_htNode(Tuple* data) {
	ht_Node* this = (ht_Node*)malloc(sizeof(struct ht_Node));
	this->data = data;
	this->next = NULL;
	return this;
}

HashTable* create_HashTable(int key)
{
	HashTable* this = (HashTable*)malloc(sizeof(struct HashTable));
	this->buckets = (ht_Node**)malloc(1009*sizeof(ht_Node*));
	for(int i = 0; i < 1009; i++)
		this->buckets[i] = NULL;
	this->key = key;
	this->count = 0;
	return this;
}


void ht_put(HashTable* h, Tuple* t)
{
	int hashed_value = hash(h->key, t);
	ht_Node* bucket = h->buckets[hash(h->key, t)];
	if(h->buckets[hashed_value] == NULL) {
		h->buckets[hashed_value] = create_htNode(t);
	} 
	else {
		for(ht_Node* ptr = h->buckets[hashed_value]; ptr != NULL; ptr = ptr->next)
			if(ptr->next == NULL)  {
				ptr->next = create_htNode(t);
				break;
			}
	}
	h->count++;
}

TupleSet* ht_get(HashTable* h, char* key)
{
	ht_Node* bucket = h->buckets[sum_bytes(key) % 1009];
	TupleSet* set = createSet();
	for(ht_Node* ptr = bucket; ptr != NULL; ptr = ptr->next) {
		if(strcmp(key, ptr->data->data[h->key]) == 0) 
			add(set, ptr->data);
	}
	return set;
}

TupleSet* ht_getAll(HashTable* h)
{
	TupleSet* set = createSet();

	for(int i = 0; i < 1009; i++)
	{
		ht_Node* bucket = h->buckets[i];

		for(ht_Node* ptr = bucket; ptr != NULL; ptr = ptr->next) {
				add(set, ptr->data);
		}
	}

	return set;
}

