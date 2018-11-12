#ifndef _SCHEMA_H
#define _SCHEMA_H

#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"

typedef struct Schema 
{
	char** names;
	int size;
	int primary_hash;
	int* secondary_hash;
	HashTable* primary;
	HashTable** secondary;
} Schema;

Schema* create_Schema(int size, int primary_hash, int* secondary_hash, char** names);



#endif
