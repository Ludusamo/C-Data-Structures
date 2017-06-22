#include "hashtable.h"

int ctor_hashtable(Hashtable *h) {
	ctor_list(&h->a);
	ctor_list(&h->b);
	h->capacity = 0;
	return 1;
}

int dtor_hashtable(Hashtable *h) {
	dtor_list(&h->a);
	dtor_list(&h->b);
	return 1;
}

int set_hashtable(Hashtable *h, const char *key, void *val) {
	int cur = 1;
	Keyval *pair = malloc(sizeof(Keyval));
	pair->key = key;
	pair->val = val;
	while (1) {
		for (size_t i = 0; i < h->a.length; i++) {
			if (cur) {
				uint64_t hash = hash1(pair->key) % h->a.length;
				Keyval *cur_pair = access_list(&h->a, hash);
				set_list(&h->a, hash, pair);
				if (cur_pair) {
					pair = cur_pair;
					cur = !cur;
				} else {
					return 1;
				}
			} else {
				uint64_t hash = hash2(pair->key) % h->b.length;
				Keyval *cur_pair = access_list(&h->b, hash);
				set_list(&h->b, hash, pair);
				if (cur_pair) {
					pair = cur_pair;
					cur = !cur;
				} else {
					return 1;
				}
			}
		}
		_rehash(h);
	}
}

int _rehash(Hashtable *h) {
	List keyvals;
	ctor_list(&keyvals);
	for (size_t i = 0; i < h->capacity / 2; i++) {
		Keyval *a = access_list(&h->a, i);
		if (a) append_list(&keyvals, a);
		Keyval *b = access_list(&h->b, i);
		if (b) append_list(&keyvals, b);
	}
	if (h->capacity < 1) h->capacity = 1;
	clear_list(&h->a);
	clear_list(&h->b);
	resize_list(&h->a, h->capacity, 0);
	resize_list(&h->b, h->capacity, 0);
	for (size_t i = 0; i < keyvals.length; i++) {
		Keyval *keyval = access_list(&keyvals, i);
		set_hashtable(h, keyval->key, keyval->val);
		free(keyval);
	}
	dtor_list(&keyvals);
	h->capacity *= 2;
}

uint64_t hash1(const char *str) {
	uint64_t hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}

uint64_t hash2(const char *str) {
	uint64_t hash = 0;
	int c;

	while ((c = *str++))
		hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}
