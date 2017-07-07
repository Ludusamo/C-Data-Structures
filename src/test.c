#include "test.h"
#include <stdio.h>

int run_tests(const char *name,
	const Array *tests,
	Test_Helper setup,
	Test_Helper teardown) {
	printf("Running Tests for: %s\n", name);
	void *state;
	setup(&state);
	for (int i = 0; i < tests->length; i++) {
		((Test) (access_array(tests, i).bits & ~ptr_mask))(&state);
		printf("Passed\n");
	}
	teardown(&state);
	return 1;
}
