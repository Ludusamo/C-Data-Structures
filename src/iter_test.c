#include "iter_test.h"

int end_test(Iter **iter) {
	return (*iter)->cur <= *((int*)(*iter)->end_data);
}

void *next_test(Iter **iter) {
	return (*iter)->data[(*iter)->cur++];
}

static int iter_test_setup(void **state) {
	Iter_Test_Container *itc = malloc(sizeof(Iter_Test_Container));
	itc->array = calloc(sizeof(void*), 10);
	itc->iter = malloc(sizeof(Iter));

	void **arr = itc->array;

	Iter *iter = itc->iter;
	iter->end_data = malloc(sizeof(int*));
	*((int*)iter->end_data) = 10;
	for (size_t i = 0; i < 10; i++) {
		arr[i] = malloc(sizeof(int));
		*((int*)arr[i]) = i;
	}
	iter->data = arr;
		
	iter->cur = 0;
	iter->next = &next_test;
	iter->end = &end_test;

	*state = itc;
	return 0;
}

static int iter_test_teardown(void **state) {
	if (state) {
		free(((Iter_Test_Container*)*state)->array);
		free((((Iter_Test_Container*)*state)->iter)->end_data);
		for (size_t i = 0; i < 10; i++) {
			free(((Iter_Test_Container*)*state)->array[i]);
		}
		free(((Iter_Test_Container*)*state)->iter);
		free(*state);
		state = NULL;
	}
	return 0;
}

static void iter_test(void **state) {
	Iter *iter = ((Iter*)((Iter_Test_Container*)*state)->iter);
	int should_be = 0;
	void *i;
	foreach(i, iter) {
		assert_int_equal(should_be++, *((int*)i));
	}
}

int run_iter_tests() {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(iter_test)
	};

	return cmocka_run_group_tests_name("Iter Tests", tests, iter_test_setup, iter_test_teardown);
}
