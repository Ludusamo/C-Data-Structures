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
	assert_non_null(*state);
}

void dtor_list_test(void **state) {
	dtor_list(*state);
	assert_null(((List*) (*state))->array);
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
	assert_int_equal(insert_item, *(int *)access_array(list->array, 0));
	for (int i = 1; i < list->length; i++) {
		assert_int_equal(should_be++ * 7, *(int *)access_array(list->array, i));
	}
	assert_int_equal(0, insert_list(list, 400, &insert_item));
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
		assert_int_equal(should_be++ * 7, *(int *)access_array(list->array, i));
	}
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
	assert_int_equal(list->array->length, 10);
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
	assert_int_equal(list->length, 10);
	clear_list(list);
	assert_int_equal(list->length, 0);
	assert_null(list->array);
}

int run_list_tests() {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(ctor_list_test),
		cmocka_unit_test(insert_list_test),
		cmocka_unit_test(reserve_space_list_test),
		cmocka_unit_test(append_list_test),
		cmocka_unit_test(clear_list_test),
		cmocka_unit_test(dtor_list_test)
	};
	return cmocka_run_group_tests_name("List Tests", tests, list_test_setup, list_test_teardown);
}
