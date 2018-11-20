#include "Tuple.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

Tuple* create_Tuple(int n, char** data)
{
	Tuple* ret = (Tuple*)malloc(sizeof(Tuple));
	ret->n = n;
	ret->data = data;
	return ret;
}

Tuple* createTuple(int n, ...)
{
	char** tupleArgs = (char**) malloc(sizeof(char*)*n);
	va_list ap;
	va_start(ap,n);

	for (int i=0;i<n;i++)
	{
		char* val = va_arg(ap, char*);
		tupleArgs[i] = val;
	}

	va_end(ap);
	return create_Tuple(n, tupleArgs);
}

void printTuple(Tuple* t)
{
	for(int i = 0; i < t->n; i++) {
		if(i == t->n-1) printf("%s", t->data[i]);
		else printf("%s, ", t->data[i]);

	}
}

void freeTuple(Tuple* t)
{
	for(int i = 0; i < t->n; i++) {
		free(t->data[i]);
	}
	free(t->data);
	free(t);
}

int matchTuple(Tuple* main, Tuple* reg)
{
	if(main == NULL) return 0;
	for(int i = 0; i < main->n; i++) {
		if(strcmp(reg->data[i],"*") !=0 && strcmp(main->data[i], reg->data[i]) != 0) return 0;
	}
	printf("match!\n");

	return 1;
}
