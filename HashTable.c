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
	this->key_vector = key_vector;
	this->count = 0;
	return this;
}
