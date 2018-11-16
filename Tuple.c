#include "Tuple.h"
#include <stdio.h>
#include <stdlib.h>

Tuple* create_Tuple(int n, char** data)
{
	Tuple* ret = (Tuple*)malloc(sizeof(Tuple));
	ret->n = n;
	ret->data = data;
	return ret;
}

void printTuple(Tuple* t)
{
	for(int i = 0; i < t->n; i++) {
		if(i == t->n-1) printf("%s", t->data[i]);
		else printf("%s, ", t->data[i]);

	}
}
