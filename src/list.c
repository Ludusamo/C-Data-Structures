#include "list.h"

int ctor_list(List *list) {
	if (!list) {
		list = malloc(sizeof(List));
	}
	list->array = 0;
	list->length = 0;
	return 1;
}

int dtor_list(List *list) {
	if (list) {
		if (list->array) {
			dtor_array(list->array);
			free(list->array);
			list->array = 0;
		}
	}	
	return 1;
}

int append_list(List *list, void *val) {
	if (!list->array || list->array->length <= list->length) {
		_grow_list(list);
	} 
	set_array(list->array, (list->length)++, val);
	return 1;
}

size_t size_list(List *list) {
	return list->array->length;
}

int _grow_list(List *list) {
	if (!list->array) {
		list->array = malloc(sizeof(Array));
		ctor_array(list->array, 1);
	}
	Array *new_array = malloc(sizeof(Array));
	ctor_array(new_array, list->array->length * 2);
	for (size_t i = 0; i < list->array->length; i++) {
		set_array(new_array, i, access_array(list->array, i));
	}
	dtor_array(list->array);
	free(list->array);
	list->array = new_array;
	return 1;
}
