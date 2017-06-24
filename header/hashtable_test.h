#ifndef HASHTABLE_TEST_H
#define HASHTABLE_TEST_H

int hashtable_test_setup(void **state);
int hashtable_test_teardown(void **state);

void ctor_hashtable_test(void **state);
void dtor_hashtable_test(void **state);

void set_hashtable_test(void **state);
void access_hashtable_test(void **state);
void delete_hashtable_test(void **state);
void clear_hashtable_test(void **state);

int run_hashtable_tests();

#endif // HASHTABLE_TEST_H
