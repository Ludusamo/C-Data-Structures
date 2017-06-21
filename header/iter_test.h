#ifndef ITER_TEST_H
#define ITER_TEST_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>

#include "iter.h"
#include "test.h"
#include "assert.h"

typedef struct {
	int *arr;
	Iter *iter;
} Iter_Test_Container;

void next_test(Iter *self);
int done_test(const Iter *self);
void *val_test(const Iter *self);

int iter_test_setup(void **state);
int iter_test_teardown(void **state);

void iter_test(void **state);

int run_iter_tests();

#endif // ITER_TEST_H
