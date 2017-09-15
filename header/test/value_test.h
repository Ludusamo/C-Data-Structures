#ifndef VALUE_TEST_H
#define VALUE_TEST_H

#include "value.h"

int value_test_setup(void **state);
int value_test_teardown(void **state);

void value_double_test(void **state);
void value_int_test(void **state);
void value_ptr_test(void **state);
void value_obj_test(void **state);

int run_value_tests();

#endif // VALUE_TEST_H
