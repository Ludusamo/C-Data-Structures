#ifndef ARRAY_TEST_H
#define ARRAY_TEST_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>

#include "array.h"
#include "test.h"
#include "assert.h"

int array_test_setup(void **state);
int array_test_teardown(void **state);

void ctor_array_test(void **state);
void dtor_array_test(void **state);
void set_array_test(void **state);
void access_array_test(void **state);
void add_array_test(void **state);
void copy_array_test(void **state);

void iter_array_test(void **state);

int run_array_tests();

#endif // ARRAY_TEST_H
