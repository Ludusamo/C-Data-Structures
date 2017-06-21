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
void *access_list(const List *list, int index);
List *add_list(List *lhs, List *rhs);
int resize_list(List *list, size_t len, void *value);
int reserve_space_list(List *list, size_t len);

int _grow_list(List *list);

void next_iter_list(Iter *self);
int done_iter_list(const Iter *self);
void *val_iter_list(const Iter *self);

int iter_list(Iter *self, List *list);
void destroy_iter_list(Iter *self);

#endif // LIST_H
