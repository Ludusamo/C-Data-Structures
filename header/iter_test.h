#ifndef ITER_TEST_H
#define ITER_TEST_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>

#include "iter.h"
#include <cmocka.h>

typedef struct {
	int *arr;
	Iter *iter;
} Iter_Test_Container;

void next_test(Iter *self);
int done_test(const Iter *self);
void *val_test(const Iter *self);

static int iter_test_setup(void **state);
static int iter_test_teardown(void **state);

static void iter_test(void **state);

int run_iter_tests();

#endif // ITER_TEST_H
