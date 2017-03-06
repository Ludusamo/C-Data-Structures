#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct {
	void **data;
	size_t length;
} Array;

int ctor_array(Array *array, int len);
int dtor_array(Array *array);

#endif // ARRAY_H
