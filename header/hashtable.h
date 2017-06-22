#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>

#include "list.h"

typedef struct {
	const char *key;
	void *val;
} Keyval;

typedef struct {
	List a, b;
	size_t capacity;
} Hashtable;

int ctor_hashtable(Hashtable *h);
int dtor_hashtable(Hashtable *h);

Keyval *access_hashtable(const Hashtable *h, const char *key);
int set_hashtable(Hashtable *h, const char *key, void *val);
int delete_hashtable(Hashtable *h, const char *key);
int clear_hashtable(Hashtable *h);

int _rehash(Hashtable *h);

uint64_t hash1(const char *str);
uint64_t hash2(const char *str);

#endif // HASHTABLE_H
