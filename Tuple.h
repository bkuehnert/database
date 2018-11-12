#ifndef TUPLE_H_
#define TUPLE_H_

typedef struct Tuple
{
	int n;
	char** data;
} Tuple;

Tuple* create_Tuple(int n, char** data);

void printTuple(Tuple* t);

#endif
