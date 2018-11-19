#ifndef TUPLE_H_
#define TUPLE_H_

typedef struct Tuple
{
	int n;
	char** data;
} Tuple;

Tuple* create_Tuple(int n, char** data);

Tuple* createTuple(int n, ...);

void freeTuple(Tuple* t);

void printTuple(Tuple* t);

int matchTuple(Tuple* main, Tuple* exp);

int tupleEql(Tuple* a, Tuple* b);

#endif
