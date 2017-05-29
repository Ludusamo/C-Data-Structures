#include "list.h"

int ctor_list(List *list) {
	if (!list) {
		list = malloc(sizeof(List));
	}
	list->array = 0;
	return 1;
}

int dtor_list(List *list) {
	if (list) {
		if (list->array) {
			dtor_array(list->array);
			list->array = 0;
		}
	}	
	return 1;
}

size_t size_list(List *list) {
	return list->array->length;
}
