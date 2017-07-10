#ifndef OBJ_H
#define OBJ_H

typedef struct Obj_S {
	const char *type;
	void *ptr;
} Obj;

int is_type(const Obj *obj, const char *type);

#endif // OBJ_H
