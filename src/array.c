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
			free(array->data);
			array->data = 0;
		}
	}
	return 1;
}

int set_array(Array *array, int index, void *val) {
	if (!array || !(array->data) || index >= array->length) return 0;
	array->data[index] = val;
	return 1;
}

void *access_array(const Array *array, int index) {
	if (!array || !(array->data) || index >= array->length) return 0;
	return array->data[index];
}

Array *add_array(Array *arr1, Array *arr2) {
	Iter iter1, iter2;
	iter_array(&iter1, arr1);
	iter_array(&iter2, arr2);
	Array *new_array = malloc(sizeof(Array));
	ctor_array(new_array, arr1->length + arr2->length);
	int index = 0;
	Iter i;
	foreach(i, iter1) {
		set_array(new_array, index++, i.val(&i));
	}
	foreach(i, iter2) {
		set_array(new_array, index++, i.val(&i));
	}
	destroy_iter_array(&iter1);
	destroy_iter_array(&iter2);
	return new_array;
}

void next_iter_array(Iter *self) {
	*((int*)self->data[1]) += 1;
}

int done_iter_array(const Iter *self) {
	return *((int*)self->data[1]) < *((int*) self->data[2]);
}

void *val_iter_array(const Iter *self) {
	return access_array((Array*) self->data[0], *((int*) self->data[1]));
}

int iter_array(Iter *iter, Array *array) {
	iter->data = calloc(sizeof(void*), 3);
	iter->data[0] = (void*) array;
	iter->data[1] = malloc(sizeof(int));
	iter->data[2] = malloc(sizeof(int));
	*((int*)(iter->data[1])) = 0;
	*((int*)(iter->data[2])) = array->length;
	iter->next = &next_iter_array;
	iter->done = &done_iter_array;
	iter->val = &val_iter_array;
	return 1;
}

void destroy_iter_array(Iter *iter) {
	free(iter->data[1]);
	free(iter->data[2]);
	free(iter->data);
}
