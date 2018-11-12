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

int hash(const int* key_vector, Tuple* t)
{
	int sum = 0;
	for(int i = 0; i < t->n; i++) {
		if(key_vector[i]) {
			sum += sum_bytes(t->data[i]);
		}
	}
	return sum % 1009;
}

HashTable* create_HashTable(int* key_vector)
{
	HashTable* this = (HashTable*)malloc(sizeof(struct HashTable));
	this->buckets = (ht_Node**)malloc(1009*sizeof(ht_Node*));
	for(int i = 0; i < 1009; i++)
		this->buckets[i] = NULL;
	this->key_vector = key_vector;
	this->count = 0;
	return this;
}

ht_Node* create_htNode(Tuple* data) {
	ht_Node* this = (ht_Node*)malloc(sizeof(struct ht_Node));
	this->data = data;
	this->next = NULL;
	return this;
}

void ht_put(HashTable* h, Tuple* t)
{
	ht_Node* bucket = h->buckets[hash(h->key_vector, t)];
	for(ht_Node* ptr = bucket; ptr != NULL; ptr = ptr->next)
		if(ptr->next == NULL) ptr->next = create_htNode(t);
	h->count++;
}

