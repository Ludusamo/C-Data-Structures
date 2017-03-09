#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct {
	void **data;
	size_t length;
} Array;

int ctor_array(Array *array, size_t len);
int dtor_array(Array *array);

int insert_array(Array *array, int index, void *val);

#endif // ARRAY_H