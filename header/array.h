#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <string.h>
#include "iter.h"

typedef struct {
	void **data;
	size_t length;
} Array;

int ctor_array(Array *array, size_t len);
int dtor_array(Array *array);

int set_array(Array *array, int index, void *val);
void *access_array(Array *array, int index);
Array *add_array(Array *arr1, Array *arr2);

void *next_iter_array(Iter *iter);
int end_iter_array(Iter *iter);
int iter_array(Iter *iter, Array *array);

#endif // ARRAY_H
