#include "hashtable_test.h"
#include "hashtable.h"
#include "assert.h"
#include "test.h"

int hashtable_test_setup(void **state) {
    return 1;
}

int hashtable_test_teardown(void **state) {
    return 1;
}

void ctor_hashtable_test(void **state) {
    Hashtable h;
    ctor_hashtable(&h);
    assert(h.size == 0);
}

void dtor_hashtable_test(void **state) {
    Hashtable h;
    ctor_hashtable(&h);
    dtor_hashtable(&h);
}

void set_hashtable_test(void **state) {
    Hashtable h;
    ctor_hashtable(&h);

    List keys;
    ctor_list(&keys);
    append_list(&keys, from_ptr("Test"));
    append_list(&keys, from_ptr("Test2"));
    append_list(&keys, from_ptr("Test3"));
    append_list(&keys, from_ptr("Test4"));
    Iter i;
    iter_list(&i, &keys);
    int val = 0;
    foreach (i) {
        set_hashtable(&h, (char*) get_ptr(i.val(&i)), from_double(val++));
        assert(h.size == val);
    }
    destroy_iter_list(&i);
    iter_list(&i, &keys);
    val = 0;
    foreach (i) {
        Keyval *l1 = get_ptr(
            access_list(&h.a, hash1(get_ptr(i.val(&i))) % h.a.length));
        Keyval *l2 = get_ptr(
            access_list(&h.b, hash2(get_ptr(i.val(&i))) % h.b.length));
        if (l1 && l2) {
            assert((l1->key == get_ptr(i.val(&i)) &&
                l1->val.as_int32 == val) ||
                (l2->key == get_ptr(i.val(&i)) &&
                l2->val.as_int32 == val));
        } else if (l1) {
            assert(l1->key == get_ptr(i.val(&i)) &&
                 l1->val.as_int32 == val);
        } else if (l2) {
            assert(l2->key == get_ptr(i.val(&i)) &&
                 l2->val.as_int32 == val);
        }
        val++;
    }
    destroy_iter_list(&i);
    int a = 17;
    set_hashtable(&h, get_ptr(access_list(&keys, 0)), from_double(a));
    Keyval *l1 = get_ptr(access_list(&h.a, hash1("Test") % h.a.length));
    Keyval *l2 = get_ptr(access_list(&h.b, hash2("Test") % h.b.length));
    if (l1 && l2) {
        assert(l1->key == "Test" ^ l2->key == "Test");
    } else if (l1) {
        assert(l1->key == "Test" && l1->val.as_int32 == a);
    } else if (l2) {
        assert(l2->key == "Test" && l2->val.as_int32 == a);
    }
    dtor_list(&keys);
    dtor_hashtable(&h);
}

void access_hashtable_test(void **state) {
    Hashtable h;
    List keys;
    ctor_list(&keys);
    append_list(&keys, from_ptr("Test"));
    append_list(&keys, from_ptr("Test2"));
    append_list(&keys, from_ptr("Test3"));
    append_list(&keys, from_ptr("Test4"));
    append_list(&keys, from_ptr("Test5"));
    append_list(&keys, from_ptr("Test6"));
    append_list(&keys, from_ptr("Test7"));
    append_list(&keys, from_ptr("Test8"));
    append_list(&keys, from_ptr("Test9"));
    append_list(&keys, from_ptr("Test10"));
    ctor_hashtable(&h);
    assert(access_hashtable(&h, "test").bits == nil_val.bits);
    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
        set_hashtable(&h, get_ptr(access_list(&keys, i)), from_double(i));
    }
    for (int i = 0; i < 10; i++) {
        assert(access_hashtable(&h, 
               get_ptr(access_list(&keys, i))).as_int32 == i);
    }
    assert(nil_val.bits == access_hashtable(&h, "Random String").bits);
    dtor_list(&keys);
    dtor_hashtable(&h);
}

void delete_hashtable_test(void **state) {
    Hashtable h;
    List keys;
    ctor_list(&keys);
    append_list(&keys, from_ptr("Test"));
    append_list(&keys, from_ptr("Test2"));
    append_list(&keys, from_ptr("Test3"));
    append_list(&keys, from_ptr("Test4"));
    append_list(&keys, from_ptr("Test5"));
    append_list(&keys, from_ptr("Test6"));
    append_list(&keys, from_ptr("Test7"));
    append_list(&keys, from_ptr("Test8"));
    append_list(&keys, from_ptr("Test9"));
    append_list(&keys, from_ptr("Test10"));
    ctor_hashtable(&h);
    for (int i = 0; i < 10; i++) {
        set_hashtable(&h, get_ptr(access_list(&keys, i)), from_double(i));
    }
    delete_hashtable(&h, "Test2");
    assert(h.size == 9);
    assert(nil_val.bits == access_hashtable(&h, "Test2").bits);
    dtor_list(&keys);
    dtor_hashtable(&h);
}

void clear_hashtable_test(void **state) {
    Hashtable h;
    List keys;
    ctor_list(&keys);
    append_list(&keys, from_ptr("Test"));
    append_list(&keys, from_ptr("Test2"));
    append_list(&keys, from_ptr("Test3"));
    append_list(&keys, from_ptr("Test4"));
    append_list(&keys, from_ptr("Test5"));
    append_list(&keys, from_ptr("Test6"));
    append_list(&keys, from_ptr("Test7"));
    append_list(&keys, from_ptr("Test8"));
    append_list(&keys, from_ptr("Test9"));
    append_list(&keys, from_ptr("Test10"));
    ctor_hashtable(&h);
    for (int i = 0; i < 10; i++) {
        set_hashtable(&h, get_ptr(access_list(&keys, i)), from_double(i));
    }
    clear_hashtable(&h);
    for (int i = 0; i < 10; i++) {
        assert(nil_val.bits ==
               access_hashtable(&h, get_ptr(access_list(&keys, i))).bits);
    }
    assert(h.size == 0);
    assert(h.capacity == 0);
    dtor_list(&keys);
    dtor_hashtable(&h);
}

void copy_hashtable_test(void **state) {
    Hashtable h;
    ctor_hashtable(&h);
    List keys;
    ctor_list(&keys);
    append_list(&keys, from_ptr("Test"));
    append_list(&keys, from_ptr("Test2"));
    append_list(&keys, from_ptr("Test3"));
    append_list(&keys, from_ptr("Test4"));
    append_list(&keys, from_ptr("Test5"));
    append_list(&keys, from_ptr("Test6"));
    append_list(&keys, from_ptr("Test7"));
    append_list(&keys, from_ptr("Test8"));
    append_list(&keys, from_ptr("Test9"));
    append_list(&keys, from_ptr("Test10"));
    for (int i = 0; i < 10; i++) {
        set_hashtable(&h, get_ptr(access_list(&keys, i)), from_double(i));
    }
    Hashtable copy;
    ctor_hashtable(&copy);
    copy_hashtable(&h, &copy);
    for (size_t i = 0; i < keys.length; i++) {
        const char *key = get_ptr(access_list(&keys, i));
        assert(access_hashtable(&h, key).bits == access_hashtable(&copy, key).bits);
    }
    dtor_hashtable(&copy);
    dtor_hashtable(&h);
    dtor_list(&keys);
}

void iter_hashtable_test(void **state) {
    Hashtable h;
    List keys;
    ctor_list(&keys);
    append_list(&keys, from_ptr("Test"));
    append_list(&keys, from_ptr("Test2"));
    append_list(&keys, from_ptr("Test3"));
    append_list(&keys, from_ptr("Test4"));
    append_list(&keys, from_ptr("Test5"));
    append_list(&keys, from_ptr("Test6"));
    append_list(&keys, from_ptr("Test7"));
    append_list(&keys, from_ptr("Test8"));
    append_list(&keys, from_ptr("Test9"));
    append_list(&keys, from_ptr("Test10"));
    ctor_hashtable(&h);
    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
        set_hashtable(&h, get_ptr(access_list(&keys, i)), from_double(i));
    }
    Iter i;
    iter_hashtable(&i, &h);
    foreach (i) {
        assert(i.val(&i).bits != nil_val.bits);
    }
    destroy_iter_hashtable(&i);
    dtor_list(&keys);
    dtor_hashtable(&h);
}
int run_hashtable_tests() {
    Array tests;
    ctor_array(&tests, 8);
    set_array(&tests, 0, from_ptr(ctor_hashtable_test));
    set_array(&tests, 1, from_ptr(set_hashtable_test));
    set_array(&tests, 2, from_ptr(access_hashtable_test));
    set_array(&tests, 3, from_ptr(delete_hashtable_test));
    set_array(&tests, 4, from_ptr(clear_hashtable_test));
    set_array(&tests, 5, from_ptr(copy_hashtable_test));
    set_array(&tests, 6, from_ptr(iter_hashtable_test));
    set_array(&tests, 7, from_ptr(dtor_hashtable_test));

    int ret = run_tests("Hashtable Tests",
        &tests,
        hashtable_test_setup,
        hashtable_test_teardown);
    dtor_array(&tests);
    return ret;
}
