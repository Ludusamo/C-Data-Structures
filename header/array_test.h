#ifndef ARRAY_TEST_H
#define ARRAY_TEST_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>

#include "array.h"
#include <cmocka.h>

static int array_test_setup(void **state);
static int array_test_teardown(void **state);

static void ctor_array_test(void **state);
static void dtor_array_test(void **state);
static void insert_array_test(void **state);
static void access_array_test(void **state);
static void add_array_test(void **state);

static void iter_array_test(void **state);

int run_array_tests();

#endif // ARRAY_TEST_H
