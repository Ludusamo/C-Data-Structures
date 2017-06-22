#include "hashtable_test.h"
#include "hashtable.h"
#include "assert.h"
#include "test.h"

int hashtable_test_setup(void **state) {
	return 1;
}

int hashtable_test_teardown(void **state) {
	return 1;
}

void ctor_hashtable_test(void **state) {
	Hashtable h;
	ctor_hashtable(&h);
}

void dtor_hashtable_test(void **state) {
	Hashtable h;
	ctor_hashtable(&h);
	dtor_hashtable(&h);
}

int run_hashtable_tests() {
	Array tests;
	ctor_array(&tests, 2);
	set_array(&tests, 0, ctor_hashtable_test);
	set_array(&tests, 1, dtor_hashtable_test);

	return run_tests("Hashtable Tests",
		&tests,
		hashtable_test_setup,
		hashtable_test_teardown);
}
