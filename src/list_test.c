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

int run_list_tests() {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(ctor_list_test),
		cmocka_unit_test(dtor_list_test)
	};
	return cmocka_run_group_tests_name("List Tests", tests, list_test_setup, list_test_teardown);
}
