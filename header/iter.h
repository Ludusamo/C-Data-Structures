#ifndef ITER_H
#define ITER_H

#define foreach(var, iter) for(var = iter.next(&iter); iter.end(&iter); var= iter.next(&iter))

typedef struct Iter Iter;

struct Iter {
	void **data;
	void **end_data;
	int cur;
	void *(*next)(Iter *iter);
	int (*end)(Iter *iter);
};

#endif // ITER_H
