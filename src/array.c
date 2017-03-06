#include "array.h"

int ctor_array(Array *array, int len) {
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
			array->data = NULL;
		}
	}
	return 1;
}
