#include "Tuple.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
	for(int i = 0; i < t->n; i++)
		printf("%s, ", t->data[i]);
	printf("\n");
}
