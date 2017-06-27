#ifndef ITER_H
#define ITER_H

#define foreach(var, iter_ctor) Iter var;\
                                for(var = iter; var.done(&var); var.next(&var))

typedef struct Iter Iter;

struct Iter {
	void **data;
	void (*next)(Iter *self);
	int (*done)(const Iter *self);
	void *(*val)(const Iter *self);
};

#endif // ITER_H
