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
