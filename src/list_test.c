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
	assert(((List*) (*state))->array == 0);
}

void insert_list_test(void **state) {
	List *list = ((List *) *state);
	int arr[32];
	for (int i = 0; i < 32; i++) {
		arr[i] = i * 7;
		append_list(list, &arr[i]);
	}
	int insert_item = 25;
	insert_list(list, 0, &insert_item);
	int should_be = 0;
	assert(insert_item == *(int *)access_array(list->array, 0));
	for (int i = 1; i < list->length; i++) {
		assert(should_be++ * 7 == *(int *)access_array(list->array, i));
	}
	assert(0 == insert_list(list, 400, &insert_item));
}

void append_list_test(void **state) {
	List *list = ((List *) *state);
	int arr[32];
	for (int i = 0; i < 32; i++) {
		arr[i] = i * 7;
		append_list(list, &arr[i]);
	}
	int should_be = 0;
	for (int i = 0; i < list->length; i++) {
		assert(should_be++ * 7 == *(int *)access_array(list->array, i));
	}
}

void resize_list_test(void **state) {
	List *list = *state;
	clear_list(list);
	int val = 17;
	resize_list(list, 100, &val);
	assert(100 == list->length);
	assert(17 == *((int *) access_array(list->array, 25)));
}

void reserve_space_list_test(void **state) {
	List *list = *state;
	if (list->array) {
		dtor_array(list->array);
		free(list->array);
		list->array = 0;
		list->length = 0;
	}
	reserve_space_list(list, 10);
	assert(list->array->length == 10);
}

void clear_list_test(void **state) {
	List *list = *state;
	list->length = 0;
	reserve_space_list(list, 10000);
	int arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = i;
		append_list(list, &arr[i]);
	}
	assert(list->length == 10);
	clear_list(list);
	assert(list->length == 0);
	assert(list->array == 0);
}

void set_list_test(void **state) {
	List *list = *state;
	list->length = 0;
	reserve_space_list(list, 10);
	int a = 10;
	set_list(list, 0, &a);
	assert(*((int*)list->array->data[0]) == a);
	set_list(list, 2, &a);
	assert(*((int*)list->array->data[2]) == a);
	assert(!set_list(list, 11, &a));
}

void access_list_test(void **state) {
	List *list = *state;
	list->length = 0;
	reserve_space_list(list, 10);
	int a = 10;
	set_list(list, 0, &a);
	assert(*(int *) access_list(list, 0) == a);
	set_list(list, 2, &a);
	assert(*(int *) access_list(list, 2) == a);
	assert(!access_list(list, 11));
}

void add_list_test(void **state) {
	List l1, l2;
	ctor_list(&l1);
	ctor_list(&l2);
	int a[10];
	for (int i = 0; i < 10; i++) {
		a[i] = i;
		append_list(&l1, &a[i]);
	}
	int b[10];
	for (int i = 10; i < 20; i++) {
		b[i - 10] = i;
		append_list(&l2, &b[i - 10]);
	}
	List *l3 = add_list(&l1, &l2);
	for (int i = 0; i < 10; i++) {
		assert(*(int *) access_list(l3, i) == a[i]);
	}
	for (int i = 10; i < 20; i++) {
		assert(*(int *) access_list(l3, i) == b[i - 10]);
	}
}

void iter_list_test(void **state) {
	List l1;
	ctor_list(&l1);
	int a[10];
	for (int i = 0; i < 10; i++) {
		a[i] = i;
		append_list(&l1, &a[i]);
	}
	Iter iter;
	iter_list(&iter, &l1);
	Iter i;
	int should_be = 0;
	foreach(i, iter) {
		assert(should_be++ == *(int*) i.val(&i));
	}
	destroy_iter_list(&iter);
}

int run_list_tests() {
	Array tests;
	ctor_array(&tests, 10);
	set_array(&tests, 0, ctor_list_test);
	set_array(&tests, 1, insert_list_test);
	set_array(&tests, 2, resize_list_test);
	set_array(&tests, 3, reserve_space_list_test);
	set_array(&tests, 4, append_list_test);
	set_array(&tests, 5, clear_list_test);
	set_array(&tests, 6, set_list_test);
	set_array(&tests, 7, access_list_test);
	set_array(&tests, 7, add_list_test);
	set_array(&tests, 8, iter_list_test);
	set_array(&tests, 9, dtor_list_test);
	return run_tests("List Tests", &tests, list_test_setup, list_test_teardown);
}
