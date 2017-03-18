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

int insert_array(Array *array, int index, void *val);
void *access_array(Array *array, int index);
Array *add_array(Array *arr1, Array *arr2);

void *next_iter_array(Iter **iter);
int end_iter_array(Iter **iter);
Iter *iter_array(Array *array);
void destroy_iter_array(Iter *iter);

#endif // ARRAY_H
