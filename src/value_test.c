#include "value_test.h"
#include <stdlib.h>
#include <assert.h>
#include "array.h"
#include "test.h"

int value_test_setup(void **state) {
	*state = malloc(sizeof(Value));
	return 1;
}

int value_test_teardown(void **state) {
	free(*state);
	state = 0;
	return 1;
}

void value_double_test(void **state) {
	*(Value*)(*state) = from_double(3.1f);
	assert(is_double(*(Value*)*state));
	assert(((Value*) *state)->as_double == 3.1f);
}

void value_int_test(void **state) {
	*(Value*)(*state) = from_double(59221);
	assert(is_int32(*(Value*)*state));
	assert(((Value*)*state)->as_int32 == 59221);
}

void value_ptr_test(void **state) {
	char *str = "Test String";
	*(Value*)(*state) = from_ptr(str);
	assert(is_ptr(*(Value*)*state));
	assert((char*) (((Value*) *state)->bits & ~ptr_mask) == str);
}

int run_value_tests() {
	Array tests;
	ctor_array(&tests, 3);
	set_array(&tests, 0, value_double_test);
	set_array(&tests, 1, value_int_test);
	set_array(&tests, 2, value_ptr_test);

	int ret = run_tests("Value Tests",
	                    &tests,
	                    value_test_setup,
	                    value_test_teardown);
	dtor_array(&tests);
	return ret;
}
