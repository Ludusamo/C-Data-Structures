#ifndef TEST_H
#define TEST_H

#include "array.h"

typedef void (*Test)(void**state);
typedef int (*Test_Helper)(void**state);

int run_tests( const char *name, const Array *tests, Test_Helper setup, Test_Helper teardown);

#endif // TEST_H
