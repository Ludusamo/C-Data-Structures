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

int insert_list(List *list, int index, void *val) {
	if (index > list->length || index < 0) return 0;
	if (!list->array || list->array->length < list->length + 1)
		_grow_list(list);
	for (size_t i = list->length; i > index; --i) {
		set_array(list->array, i, access_array(list->array, i - 1));
	}
	set_array(list->array, index, val);
	list->length++;
	return 1;
}

int append_list(List *list, void *val) {
	if (!list->array || list->array->length <= list->length) {
		_grow_list(list);
	} 
	set_array(list->array, (list->length)++, val);
	return 1;
}

int reserve_space_list(List *list, size_t len) {
	if (list->array && list->array->length >= len) return 1;
	if (!list->array) {
		list->array = malloc(sizeof(Array));
		ctor_array(list->array, 1);
	}
	Array *new_array = malloc(sizeof(Array));
	ctor_array(new_array, len);
	for (size_t i = 0; i < list->array->length; i++) {
		set_array(new_array, i, access_array(list->array, i));
	}
	dtor_array(list->array);
	free(list->array);
	list->array = new_array;
	return 1;
}

int _grow_list(List *list) {
	return reserve_space_list(list, list->array ? list->array->length * 2 : 1);
}
