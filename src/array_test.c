#include "array_test.h"

static int array_test_setup(void **state) {
	Array *arr = malloc(sizeof(Array));
	if (!arr) {
		return -1;
	}

	*state = arr;
	return 0;
}

static int array_test_teardown(void **state) {
	if (state) {
		free(*state);
		state = NULL;
	}
	return 0;
}

static void ctor_array_test(void **state) {
	ctor_array(*state, 10);
	assert_non_null(*state);
}

static void dtor_array_test(void **state) {
	dtor_array(*state);
	assert_null(((Array *) (*state))->data);
}

static void insert_array_test(void **state) {
	int a = 10;
	insert_array(*state, 0, &a);
	assert_int_equal(a, *(int*)(((Array *)(*state))->data[0]));
	int b = 20;
	insert_array(*state, 5, &b);
	assert_int_equal(b, *(int*)(((Array *)(*state))->data[5]));
	insert_array(*state, 0, &b);
	assert_int_equal(b, *(int*)(((Array *)(*state))->data[0]));
}

static void access_array_test(void **state) {
	int *a = (int *) access_array(*state, 0);
	assert_int_equal(20, *a);
	int *b = (int *) access_array(*state, 5);
	assert_int_equal(20, *b);
}

int run_array_tests() {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(ctor_array_test),
		cmocka_unit_test(insert_array_test),
		cmocka_unit_test(access_array_test),
		cmocka_unit_test(dtor_array_test)
	};

	return cmocka_run_group_tests_name("Array Tests", tests, array_test_setup, array_test_teardown);
}
