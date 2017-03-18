#include "array.h"

int ctor_array(Array *array, size_t len) {
	if (!array) {
		array = malloc(sizeof(Array));
	}
	array->data = calloc(sizeof(void*), len);
	array->length = len;
	return 1;
}

int dtor_array(Array *array) {
	if (array) {
		if (array->data) {
			for (size_t i = 0; i < array->length; i++) {
				if (array->data[i]) {
					free(array->data[i]);
					array->data[i] = NULL;
				}
			}
			free(array->data);
			array->data = NULL;
		}
	}
	return 1;
}

int insert_array(Array *array, int index, void *val) {
	if (!array || !(array->data)) return 0;
	if (array->data[index]) free(array->data[index]);
	array->data[index] = malloc(sizeof(val));
	memcpy(array->data[index], val, sizeof(int));
	return 1;
}

void *access_array(Array *array, int index) {
	if (!array || !(array->data)) return NULL;
	return array->data[index];
}

Array *add_array(Array *arr1, Array *arr2) {
	Iter *iter1 = iter_array(arr1);
	Iter *iter2 = iter_array(arr2);
	Array *new_array = malloc(sizeof(Array));
	ctor_array(new_array, arr1->length + arr2->length);
	int index = 0;
	void *i;
	foreach(i, iter1) {
		new_array->data[index++] = i;
	}
	foreach(i, iter2) {
		new_array->data[index++] = i;
	}
	free(iter1);
	free(iter2);
	return new_array;
}

void *next_iter_array(Iter **iter) {
	return access_array(((Array*)((*iter)->data)), (*iter)->cur++);
}

int end_iter_array(Iter **iter) {
	return (*iter)->cur <= *((int*)(*iter)->end_data);
}

Iter *iter_array(Array *array) {
	Iter *iter = malloc(sizeof(Iter));
	iter->data = (void*) array;
	iter->end_data = (void*) &(array->length);
	iter->cur = 0;
	iter->next = &next_iter_array;
	iter->end = &end_iter_array;
	return iter;
}
