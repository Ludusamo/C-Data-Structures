#ifndef LIST_TEST_H
#define LIST_TEST_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>

#include "list.h"
#include "test.h"
#include "assert.h"

int list_test_setup(void **state);
int list_test_teardown(void **state);

void ctor_list_test(void **state);
void dtor_list_test(void **state);

void insert_list_test(void **state);
void append_list_test(void **state);
void resize_list_test(void **state);
void reserve_space_list_test(void **state);
void clear_list_test(void **state);

int run_list_tests();

#endif // LIST_TEST_H
