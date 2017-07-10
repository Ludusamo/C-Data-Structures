#include "value_test.h"
#include <stdlib.h>
#include <assert.h>
#include "array.h"
#include "test.h"
#include "obj.h"

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
	*(Value*)(*state) = from_double(3);
	assert(!is_double(*(Value*)*state));
}

void value_int_test(void **state) {
	*(Value*)(*state) = from_double(59221);
	assert(is_int32(*(Value*)*state));
	assert(((Value*)*state)->as_int32 == 59221);
	*(Value*)(*state) = from_double(3.1);
	assert(!is_int32(*(Value*)*state));
}

void value_ptr_test(void **state) {
	char *str = "Test String";
	*(Value*)(*state) = from_ptr(str);
	assert(is_ptr(*(Value*)*state));
	assert((char*) (((Value*) *state)->bits & ~ptr_mask) == str);
	str = "New string";
	assert((char*) (((Value*) *state)->bits & ~ptr_mask) != str);
}

void value_obj_test(void **state) {
	int a = 33;
	Obj o = (Obj) { "int", &a };
	*(Value*)(*state) = from_obj(&o);
	assert(is_obj(*(Value*)*state));
	assert(get_obj(*(Value*)*state)->type == "int");
	assert(*(int*) (get_obj(*(Value*)*state)->ptr) == a);
}

int run_value_tests() {
	Array tests;
	ctor_array(&tests, 4);
	set_array(&tests, 0, from_ptr(value_double_test));
	set_array(&tests, 1, from_ptr(value_int_test));
	set_array(&tests, 2, from_ptr(value_ptr_test));
	set_array(&tests, 3, from_ptr(value_obj_test));

	int ret = run_tests("Value Tests",
	                    &tests,
	                    value_test_setup,
	                    value_test_teardown);
	dtor_array(&tests);
	return ret;
}
