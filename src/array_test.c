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
		state = 0;
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

static void set_array_test(void **state) {
	int *a = malloc(sizeof(int));
	*a = 10;
	set_array(*state, 0, a);
	assert_int_equal(*a, *(int*)(((Array *)(*state))->data[0]));
	int *b = malloc(sizeof(int));
	*b = 20;
	set_array(*state, 5, b);
	assert_int_equal(*b, *(int*)(((Array *)(*state))->data[5]));
	set_array(*state, 0, b);
	assert_int_equal(*b, *(int*)(((Array *)(*state))->data[0]));
	free(a);
	free(b);
}

static void access_array_test(void **state) {
	int *a = malloc(sizeof(int));
	*a = 20;
	set_array(*state, 0, a);
	int *b = malloc(sizeof(int));
	*b = 20;
	set_array(*state, 5, b);
	int *c = (int *) access_array(*state, 0);
	assert_int_equal(20, *c);
	int *d = (int *) access_array(*state, 5);
	assert_int_equal(20, *d);
	free(a);
	free(b);
}

static void add_array_test(void **state) {
	int *testArr = calloc(sizeof(int), ((Array*)(*state))->length);
	for (int i = 0; i < ((Array*)(*state))->length; i++) {
		testArr[i] = i;
		set_array(*state, i, &testArr[i]);
	}
	Array *added_array = add_array(*state, *state);
	int should_be = 0;
	Iter iter;
	iter_array(&iter, added_array);
	Iter i;
	foreach(i, iter) {
		assert_int_equal((should_be++) % 10, *(int*)i.val(&i));
	}
	destroy_iter_array(&iter);
	dtor_array(added_array);
	free(testArr);
	free(added_array);
}

static void iter_array_test(void **state) {
	int *testArr = calloc(sizeof(int), ((Array*)(*state))->length);
	for (int i = 0; i < ((Array*)(*state))->length; i++) {
		testArr[i] = i;
		set_array(*state, i, &testArr[i]);
	}
	int should_be = 0;
	Iter iter;
	iter_array(&iter, *state);
	Iter i;
	foreach(i, iter) {
		assert_int_equal(should_be++, *((int*)i.val(&i)));
	}
	destroy_iter_array(&iter);
	free(testArr);
}

int run_array_tests() {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(ctor_array_test),
		cmocka_unit_test(set_array_test),
		cmocka_unit_test(access_array_test),
		cmocka_unit_test(iter_array_test),
		cmocka_unit_test(add_array_test),
		cmocka_unit_test(dtor_array_test)
	};

	return cmocka_run_group_tests_name("Array Tests", tests, array_test_setup, array_test_teardown);
}
