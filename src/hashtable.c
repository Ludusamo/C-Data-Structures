#include "hashtable.h"

int ctor_hashtable(Hashtable *h) {
	ctor_list(&h->a);
	ctor_list(&h->b);
	return 1;
}

int dtor_hashtable(Hashtable *h) {
	dtor_list(&h->a);
	dtor_list(&h->b);
	return 1;
}
