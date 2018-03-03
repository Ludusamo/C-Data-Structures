#include "array_test.h"

int array_test_setup(void **state) {
    Array *arr = malloc(sizeof(Array));
    if (!arr) {
        return -1;
    }

    *state = arr;
    return 0;
}

int array_test_teardown(void **state) {
    if (state) {
        free(*state);
        state = 0;
    }
    return 0;
}

void ctor_array_test(void **state) {
    ctor_array(*state, 10);
    assert(*state != 0);
}

void dtor_array_test(void **state) {
    dtor_array(*state);
    assert(((Array *) (*state))->data == 0);
}

void set_array_test(void **state) {
    int a = 10;
    set_array(*state, 0, from_double(a));
    assert(is_int32((((Array *)(*state))->data[0])));
    assert(a == (((Array *)(*state))->data[0]).as_int32);
    int b = 20;
    set_array(*state, 5, from_double(b));
    assert(is_int32(((Array *)(*state))->data[5]));
    assert(b == (((Array *)(*state))->data[5]).as_int32);
    set_array(*state, 0, from_double(b));
    assert(is_int32((((Array *)(*state))->data[0])));
    assert(b == (((Array *)(*state))->data[5]).as_int32);
}

void access_array_test(void **state) {
    int a = 20;
    set_array(*state, 0, from_double(a));
    int b = 20;
    set_array(*state, 5, from_double(b));
    int c = access_array(*state, 0).as_int32;
    assert(20 == c);
    int d = access_array(*state, 5).as_int32;
    assert(20 == d);
}

void add_array_test(void **state) {
    for (int i = 0; i < ((Array*)(*state))->length; i++) {
        set_array(*state, i, from_double(i));
    }
    Array *added_array = add_array(*state, *state);
    int should_be = 0;
    Iter i;
    iter_array(&i, *state);
    foreach(i) {
        assert((should_be++) == i.val(&i).as_int32);
    }
    destroy_iter_array(&i);
    dtor_array(added_array);
    free(added_array);
}

void copy_array_test(void **state) {
    Array array;
    ctor_array(&array, 10);
    for (int i = 0; i < array.length; i++) {
        set_array(&array, i, from_double(i));
    }
    Array copy_same;
    ctor_array(&copy_same, 10);
    copy_array(&array, &copy_same);
    Array copy_not_same;
    ctor_array(&copy_not_same, 15);
    copy_array(&array, &copy_not_same);
    for (int i = 0; i < array.length; i++) {
        assert(copy_same.data[i].bits == array.data[i].bits);
        assert(copy_not_same.data[i].bits == array.data[i].bits);
    }
    assert(copy_not_same.length == array.length);
    dtor_array(&array);
    dtor_array(&copy_same);
    dtor_array(&copy_not_same);
}

void iter_array_test(void **state) {
    for (int i = 0; i < ((Array*)(*state))->length; i++) {
        set_array(*state, i, from_double(i));
    }
    int should_be = 0;
    Iter i;
    iter_array(&i, *state);
    foreach(i) {
        assert(should_be++ == i.val(&i).as_int32);
    }
    destroy_iter_array(&i);
}

int run_array_tests() {
    Array tests;
    ctor_array(&tests, 7);
    set_array(&tests, 0, from_ptr(ctor_array_test));
    set_array(&tests, 1, from_ptr(set_array_test));
    set_array(&tests, 2, from_ptr(access_array_test));
    set_array(&tests, 3, from_ptr(iter_array_test));
    set_array(&tests, 4, from_ptr(add_array_test));
    set_array(&tests, 5, from_ptr(copy_array_test));
    set_array(&tests, 6, from_ptr(dtor_array_test));

    int ret = run_tests("Array Tests", &tests, array_test_setup, array_test_teardown);
    dtor_array(&tests);
    return ret;
}
