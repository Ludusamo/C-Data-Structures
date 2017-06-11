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

void append_list_test(void **state) {
	List *list = ((List *) *state);
	int arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = i * 7;
		append_list(list, &arr[i]);
	}
	printf("List Length: %d\n", list->length);
	printf("List Capacity: %d\n", list->array->length);
	int should_be = 0;
	for (int i = 0; i < list->length; i++) {
		assert_int_equal(should_be++ * 7, *(int *)access_array(list->array, i));
	}
}

int run_list_tests() {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(ctor_list_test),
		cmocka_unit_test(append_list_test),
		cmocka_unit_test(dtor_list_test)
	};
	return cmocka_run_group_tests_name("List Tests", tests, list_test_setup, list_test_teardown);
}
