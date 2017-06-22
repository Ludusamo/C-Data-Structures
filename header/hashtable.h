#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>

#include "list.h"

typedef struct {
	void *first, *second;
} Pair;

typedef struct {
	List a, b;
} Hashtable;

int ctor_hashtable(Hashtable *h);
int dtor_hashtable(Hashtable *h);

void *access_hashtable(const Hashtable *h, void *key);
int set_hashtable(Hashtable *h, Pair *keyval);
int delete_hashtable(Hashtable *h, void *key);
int clear_hashtable(Hashtable *h);

int _rehash(Hashtable *h);

uint64_t hash1(void *ptr);
uint64_t hash2(void *ptr);

#endif // HASHTABLE_H
