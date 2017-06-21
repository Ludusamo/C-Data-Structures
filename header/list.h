#ifndef LIST_H
#define LIST_H

#include "array.h"

typedef struct {
	Array *array;
	size_t length;
} List;

int ctor_list(List *list);
int dtor_list(List *list);

int insert_list(List *list, int index, void *val);
int append_list(List *list, void *val);
int clear_list(List *list);
int set_list(List *list, int index, void *val);
void *access_list(List *list, int index);
List *add_list(List *lhs, List *rhs);
int resize_list(List *list, size_t len, void *value);
int reserve_space_list(List *list, size_t len);

int _grow_list(List *list);

#endif // LIST_H
