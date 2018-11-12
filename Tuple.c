#include "Tuple.h"
#include <stdlib.h>

Tuple* create_Tuple(int n, char** data)
{
	Tuple* ret = (Tuple*)malloc(sizeof(Tuple));
	ret->n = n;
	ret->data = data;
	return ret;
}
