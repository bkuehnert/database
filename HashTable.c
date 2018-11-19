#include "HashTable.h"
#include "Tuple.h"
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
			if(tupleEql(t, ptr->data)) break;
	}
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

ht_Node* removeHelper(ht_Node* head, Tuple* match)
{
	if(head == NULL) return NULL;

	if(matchTuple(head->data, match)) {
		ht_Node* tmp = head->next;
		htnodeFree(head);
		return removeHelper(tmp, match);
	}
	head->next = removeHelper(head->next, match);
	return head;
}

void ht_remove(HashTable* h, Tuple* t)
{
	int index = -1;
	for (int i = 0; i < t->n; i++) 
		if (strcmp(t->data[i], "*") != 0 && h->key == i) index = sum_bytes(t->data[i]) % 1009;

	if(index == -1) {
		for(int i = 0; i < 1009; i++) {
			h->buckets[i] = removeHelper(h->buckets[i], t);
		}	
	}
	else {
		h->buckets[index] = removeHelper(h->buckets[index], t);
	}
}

void htnodeFree(ht_Node* n)
{
	free(n->data);
	free(n);
}
