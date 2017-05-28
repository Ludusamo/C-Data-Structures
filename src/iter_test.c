#include "iter_test.h"
#include "stdio.h"

void next_test(Iter *self) {
	*((int*)self->data[1]) += 1;
}

int done_test(const Iter *self) {
	return *((int*)self->data[1]) != *((int*) self->data[2]);
}

void *val_test(const Iter *self) {
	return &((int*) self->data[0])[*((int*) self->data[1])];
}

static int iter_test_setup(void **state) {
	int *arr = calloc(sizeof(int), 10);
	for (int i = 0; i < 10; i++) {
		arr[i] = i;
	}

	Iter *iter = malloc(sizeof(Iter));
	iter->next = &next_test;
	iter->done = &done_test;
	iter->val = &val_test;

	iter->data = calloc(sizeof(void*), 3);

	iter->data[0] = arr;
	iter->data[1] = malloc(sizeof(int));
	iter->data[2] = malloc(sizeof(int));
	*(int*)(iter->data[1]) = 0;
	*(int*)(iter->data[2]) = 10;

	Iter_Test_Container *itc = malloc(sizeof(Iter_Test_Container));
	itc->arr = arr;
	itc->iter = iter;

	*state = itc;
	return 0;
}

static int iter_test_teardown(void **state) {
	if (state) {
		Iter_Test_Container *itc = *state;
		Iter *iter = (Iter *)itc->iter;
		free(iter->data[1]);
		free(iter->data[2]);
		free(iter->data);
		free(iter);
		free(itc->arr);
		free(itc);
		state = NULL;
	}
	return 0;
}

static void iter_test(void **state) {
	Iter_Test_Container *itc = *state;
	Iter *iter = ((Iter *) itc->iter);
	int should_be = 0;

	for (Iter *i = iter; i->done(i); i->next(i)) {
		assert_int_equal(should_be++, *((int*)i->val(i)));
	}
}

int run_iter_tests() {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(iter_test)
	};

	return cmocka_run_group_tests_name("Iter Tests", tests, iter_test_setup, iter_test_teardown);
}
