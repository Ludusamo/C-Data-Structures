#include "list.h"

int ctor_list(List *list) {
    list->array.length = 0;
    list->length = 0;
    return 1;
}

int dtor_list(List *list) {
    if (list) {
        clear_list(list);
        list->length = 0;
    }
    return 1;
}

int insert_list(List *list, int index, Value val) {
    if (index > list->length || index < 0) return 0;
    if (list->array.length < list->length + 1)
        _grow_list(list);
    for (size_t i = list->length; i > index; --i) {
        set_array(&list->array, i, access_array(&list->array, i - 1));
    }
    set_array(&list->array, index, val);
    list->length++;
    return 1;
}

int append_list(List *list, Value val) {
    if (list->array.length <= list->length) {
        _grow_list(list);
    }
    set_array(&list->array, (list->length)++, val);
    return 1;
}

Value pop_list(List *list) {
    if (!list || list->length == 0) return nil_val;
    Value val = access_list(list, list->length - 1);
    list->length--;
    return val;
}

int delete_list(List *list, int index) {
    if (!list || list->length < index || index < 0) return 0;
    for (size_t i = index; i < list->length - 1; i++) {
        set_list(list, i, access_list(list, i + 1));
    }
    list->length -= 1;
    return 1;
}

int clear_list(List *list) {
    if (!list) return 0;
    if (list->array.length > 0) dtor_array(&list->array);
    list->length = 0;
    return 1;
}

int set_list(List *list, int index, Value val) {
    return set_array(&list->array, index, val);
}

Value access_list(const List *list, int index) {
    if (!list || index >= list->length) return nil_val;
    return access_array(&list->array, index);
}

List *add_list(List *lhs, List *rhs) {
    List *new_list = malloc(sizeof(List));
    ctor_list(new_list);
    for (int i = 0; i < lhs->length; i++) {
        append_list(new_list, access_list(lhs, i));
    }
    for (int i = 0; i < rhs->length; i++) {
        append_list(new_list, access_list(rhs, i));
    }
    return new_list;
}

int resize_list(List *list, size_t len, Value value) {
    while (list->array.length < len) _grow_list(list);
    while (list->length < len) append_list(list, value);
    list->length = len;
    return 1;
}

int reserve_space_list(List *list, size_t len) {
    if (list->array.length >= len) return 1;
    if (list->array.length == 0) ctor_array(&list->array, len);
    else {
        list->array.data = realloc(list->array.data, sizeof(void*) * len);
        list->array.length = len;
    }
    return 1;
}

List *copy_list(const List *src, List *dest) {
    dest->length = 0;
    for (size_t i = 0; i < src->length; i++) {
        append_list(dest, access_list(src, i));
    }
    return dest;
}

int _grow_list(List *list) {
    return reserve_space_list(list,
        list->array.length > 0 ? list->array.length * 2 : 1);
}

void next_iter_list(Iter *self) {
    *(int*) self->data[1] += 1;
}

int done_iter_list(const Iter *self) {
    return *(int*) self->data[1] < *(int*) self->data[2];
}

Value val_iter_list(const Iter *self) {
    return access_list((List *) self->data[0], *(int*) self->data[1]);
}

int iter_list(Iter *iter, const List *list) {
    iter->data = calloc(sizeof(void*), 3);
    iter->data[0] = (List *) list;
    iter->data[1] = malloc(sizeof(int));
    iter->data[2] = malloc(sizeof(int));
    *(int*)iter->data[1] = 0;
    *(int*)iter->data[2] = list->length;
    iter->next = &next_iter_list;
    iter->done = &done_iter_list;
    iter->val = &val_iter_list;
    return 1;
}

void destroy_iter_list(Iter *iter) {
    free(iter->data[1]);
    free(iter->data[2]);
    free(iter->data);
}
