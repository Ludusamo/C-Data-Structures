#include "list_test.h"

int list_test_setup(void **state) {
	List *list = malloc(sizeof(List));
	if (!list) {
		return -1;
	}

	*state = list;
	return 0;
}

int list_test_teardown(void **state) {
	if (state) {
		free(*state);
		state = 0;
	}
	return 0;
}

void ctor_list_test(void **state) {
	ctor_list(*state);
	assert(*state != 0);
}

void dtor_list_test(void **state) {
	dtor_list(*state);
	assert(((List*) (*state))->array.data == 0);
}

void insert_list_test(void **state) {
	List *list = ((List *) *state);
	for (int i = 0; i < 32; i++) {
		append_list(list, from_double(i * 7));
	}
	int insert_item = 25;
	insert_list(list, 0, from_double(insert_item));
	int should_be = 0;
	assert(insert_item == access_array(&list->array, 0).as_int32);
	for (int i = 1; i < list->length; i++) {
		assert(should_be++ * 7 == access_array(&list->array, i).as_int32);
	}
	assert(0 == insert_list(list, 400, nil_val));
}

void delete_list_test(void **state) {
	List *list = ((List *) *state);
	list->length = 0;
	for (int i = 0; i < 10; i++) {
		append_list(list, from_double(i * 7));
	}
	int insert_item = 25;
	insert_list(list, 5, from_double(insert_item));
	delete_list(list, 5);
	int should_be = 0;
	for (int i = 0; i < list->length; i++) {
		assert(should_be++ * 7 == access_array(&list->array, i).as_int32);
	}
	assert(0 == delete_list(list, 400));
}

void append_list_test(void **state) {
	List *list = ((List *) *state);
	for (int i = 0; i < 32; i++) {
		append_list(list, from_double(i * 7));
	}
	int should_be = 0;
	for (int i = 0; i < list->length; i++) {
		assert(should_be++ * 7 == access_array(&list->array, i).as_int32);
	}
}

void pop_list_test(void **state) {
	List *list = ((List *) *state);
	clear_list(list);
	assert(pop_list(list).bits == nil_val.bits);
	for (int i = 0; i < 32; i++) {
		append_list(list, from_double(i * 7));
	}
	int32_t popped = pop_list(list).as_int32;
	assert(popped == 7 * 31);
	assert(list->length == 31);
}

void resize_list_test(void **state) {
	List *list = *state;
	clear_list(list);
	resize_list(list, 100, nil_val);
	assert(100 == list->length);
	assert(17 == access_array(&list->array, 25).as_int32);
}

void reserve_space_list_test(void **state) {
	List *list = *state;
	dtor_array(&list->array);
	list->length = 0;
	reserve_space_list(list, 10);
	assert(list->array.length == 10);
}

void clear_list_test(void **state) {
	List *list = *state;
	list->length = 0;
	reserve_space_list(list, 10000);
	for (int i = 0; i < 10; i++) {
		append_list(list, from_double(i));
	}
	assert(list->length == 10);
	clear_list(list);
	assert(list->length == 0);
	assert(list->array.data == 0);
}

void set_list_test(void **state) {
	List *list = *state;
	list->length = 0;
	reserve_space_list(list, 10);
	int a = 10;
	set_list(list, 0, from_double(a));
	assert(list->array.data[0].as_int32 == a);
	set_list(list, 2, from_double(a));
	assert(list->array.data[2].as_int32 == a);
	assert(!set_list(list, 11, from_double(a)));
}

void access_list_test(void **state) {
	List *list = *state;
	list->length = 0;
	resize_list(list, 10, nil_val);
	int a = 10;
	set_list(list, 0, from_double(a));
	assert(access_list(list, 0).as_int32 == a);
	set_list(list, 2, from_double(a));
	assert(access_list(list, 2).as_int32 == a);
	assert(access_list(list, 11).bits == nil_val.bits);
}

void add_list_test(void **state) {
	List l1, l2;
	ctor_list(&l1);
	ctor_list(&l2);
	for (int i = 0; i < 10; i++) {
		append_list(&l1, from_double(i));
	}
	for (int i = 10; i < 20; i++) {
		append_list(&l2, from_double(i));
	}
	List *l3 = add_list(&l1, &l2);
	for (int i = 0; i < 20; i++) {
		assert(access_list(l3, i).as_int32 == i);
	}
	dtor_list(&l1);
	dtor_list(&l2);
	dtor_list(l3);
	free(l3);
}

void iter_list_test(void **state) {
	List l1;
	ctor_list(&l1);
	for (int i = 0; i < 10; i++) {
		append_list(&l1, from_double(i));
	}
	Iter i;
	iter_list(&i, &l1);
	int should_be = 0;
	foreach(i) {
		assert(should_be++ == i.val(&i).as_int32);
	}
	destroy_iter_list(&i);
	dtor_list(&l1);
}

int run_list_tests() {
	Array tests;
	ctor_array(&tests, 13);
	set_array(&tests, 0, from_ptr(ctor_list_test));
	set_array(&tests, 1, from_ptr(insert_list_test));
	set_array(&tests, 2, from_ptr(delete_list_test));
	set_array(&tests, 3, from_ptr(resize_list_test));
	set_array(&tests, 4, from_ptr(reserve_space_list_test));
	set_array(&tests, 5, from_ptr(append_list_test));
	set_array(&tests, 6, from_ptr(pop_list_test));
	set_array(&tests, 7, from_ptr(clear_list_test));
	set_array(&tests, 8, from_ptr(set_list_test));
	set_array(&tests, 9, from_ptr(access_list_test));
	set_array(&tests, 10, from_ptr(add_list_test));
	set_array(&tests, 11, from_ptr(iter_list_test));
	set_array(&tests, 12, from_ptr(dtor_list_test));
	int ret = run_tests("List Tests", &tests, list_test_setup, list_test_teardown);
	dtor_array(&tests);
	return ret;
}
