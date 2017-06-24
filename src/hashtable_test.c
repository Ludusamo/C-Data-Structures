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
	append_list(&keys, "Test");
	append_list(&keys, "Test2");
	append_list(&keys, "Test3");
	append_list(&keys, "Test4");
	Iter iter;
	iter_list(&iter, &keys);
	Iter i;
	int data[keys.length];
	int val = 0;
	foreach (i, iter) {
		data[val] = val;
		set_hashtable(&h, (char *) i.val(&i), &data[val]);
		val++;
	}
	destroy_iter_list(&iter);
	iter_list(&iter, &keys);
	val = 0;
	foreach (i, iter) {
		Keyval *l1 = access_list(&h.a, hash1((char *) i.val(&i)) % h.a.length);
		Keyval *l2 = access_list(&h.b, hash2((char *) i.val(&i)) % h.b.length);
		if (l1 && l2) {
			assert((l1->key == (char*) i.val(&i) &&
				*(int*) l1->val == data[val]) ||
				(l2->key == (char*) i.val(&i) &&
				*(int*) l2->val == data[val]));
		} else if (l1) {
			assert(l1->key == (char*) i.val(&i) &&
				*(int*) l1->val == data[val]);
		} else if (l2) {
			assert(l2->key == (char*) i.val(&i) &&
				*(int*) l2->val == data[val]);
		}
		val++;
	}
	destroy_iter_list(&iter);
	int a = 17;
	set_hashtable(&h, access_list(&keys, 0), &a);
	Keyval *l1 = access_list(&h.a, hash1("Test") % h.a.length);
	Keyval *l2 = access_list(&h.b, hash2("Test") % h.b.length);
	if (l1 && l2) {
		assert(l1->key == "Test" ^ l2->key == "Test");
	} else if (l1) {
		assert(l1->key == "Test" &&
			*(int*) l1->val == a);
	} else if (l2) {
		assert(l2->key == "Test" &&
			*(int*) l2->val == a);
	}
	dtor_list(&keys);
	dtor_hashtable(&h);
}

void access_hashtable_test(void **state) {
	Hashtable h;
	List keys;
	ctor_list(&keys);
	append_list(&keys, "Test");
	append_list(&keys, "Test2");
	append_list(&keys, "Test3");
	append_list(&keys, "Test4");
	append_list(&keys, "Test5");
	append_list(&keys, "Test6");
	append_list(&keys, "Test7");
	append_list(&keys, "Test8");
	append_list(&keys, "Test9");
	append_list(&keys, "Test10");
	ctor_hashtable(&h);
	int arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = i;
		set_hashtable(&h, access_list(&keys, i), &arr[i]);
	}
	for (int i = 0; i < 10; i++) {
		assert(*(int*)access_hashtable(&h, access_list(&keys, i)) == arr[i]);
	}
	assert(!access_hashtable(&h, "Random String"));
	dtor_list(&keys);
	dtor_hashtable(&h);
}

void delete_hashtable_test(void **state) {
	Hashtable h;
	List keys;
	ctor_list(&keys);
	append_list(&keys, "Test");
	append_list(&keys, "Test2");
	append_list(&keys, "Test3");
	append_list(&keys, "Test4");
	append_list(&keys, "Test5");
	append_list(&keys, "Test6");
	append_list(&keys, "Test7");
	append_list(&keys, "Test8");
	append_list(&keys, "Test9");
	append_list(&keys, "Test10");
	ctor_hashtable(&h);
	int arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = i;
		set_hashtable(&h, access_list(&keys, i), &arr[i]);
	}
	delete_hashtable(&h, "Test2");
	assert(!access_hashtable(&h, "Test2"));
	dtor_list(&keys);
	dtor_hashtable(&h);
}

int run_hashtable_tests() {
	Array tests;
	ctor_array(&tests, 5);
	set_array(&tests, 0, ctor_hashtable_test);
	set_array(&tests, 1, set_hashtable_test);
	set_array(&tests, 2, access_hashtable_test);
	set_array(&tests, 3, delete_hashtable_test);
	set_array(&tests, 4, dtor_hashtable_test);

	int ret = run_tests("Hashtable Tests",
		&tests,
		hashtable_test_setup,
		hashtable_test_teardown);
	dtor_array(&tests);
	return ret;
}
