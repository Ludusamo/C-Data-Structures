#include "iter_test.h"
#include "stdio.h"

void next_test(Iter *self) {
    *((int*)self->data[1]) += 1;
}

int done_test(const Iter *self) {
    return *((int*)self->data[1]) != *((int*) self->data[2]);
}

Value val_test(const Iter *self) {
    return ((Value*) self->data[0])[*((int*) self->data[1])];
}

int iter_test_setup(void **state) {
    Value *arr = calloc(sizeof(Value), 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = from_double(i);
    }

    Iter *iter = malloc(sizeof(Iter));
    iter->next = &next_test;
    iter->done = &done_test;
    iter->val = &val_test;

    iter->data = calloc(sizeof(void*), 3);

    iter->data[0] = arr;
    iter->data[1] = malloc(sizeof(int));
    iter->data[2] = malloc(sizeof(int));
    *(int*)(iter->data[1]) = 0;
    *(int*)(iter->data[2]) = 10;

    Iter_Test_Container *itc = malloc(sizeof(Iter_Test_Container));
    itc->arr = arr;
    itc->iter = iter;

    *state = itc;
    return 0;
}

int iter_test_teardown(void **state) {
    if (state) {
        Iter_Test_Container *itc = *state;
        Iter *iter = (Iter *)itc->iter;
        free(iter->data[1]);
        free(iter->data[2]);
        free(iter->data);
        free(iter);
        free(itc->arr);
        free(itc);
        state = NULL;
    }
    return 0;
}

void iter_test(void **state) {
    Iter_Test_Container *itc = *state;
    Iter *iter = ((Iter *) itc->iter);
    int should_be = 0;

    for (Iter *i = iter; i->done(i); i->next(i)) {
        assert(should_be++ == i->val(i).as_int32);
    }
}

int run_iter_tests() {
    Array tests;
    ctor_array(&tests, 1);
    set_array(&tests, 0, from_ptr(iter_test));

    int ret = run_tests("Iter Tests",
        &tests,
        iter_test_setup,
        iter_test_teardown);
    dtor_array(&tests);
    return ret;
}
