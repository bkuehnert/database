#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tuple.h"

typedef struct SetNode Node;

typedef struct TupleSet TupleSet;

Set* createSet();

void add(Set* list, Tuple* add);

int indexOf(Set* list, Tuple* checkTuple);

void freeList(Set* list);

#endif
