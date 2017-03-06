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


int run_array_tests() {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(ctor_array_test),
		cmocka_unit_test(dtor_array_test)
	};

	return cmocka_run_group_tests_name("Array Tests", tests, array_test_setup, array_test_teardown);
}
