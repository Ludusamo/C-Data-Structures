#ifndef OBJ_H
#define OBJ_H

typedef struct Obj_S {
	const char *type;
	void *ptr;
} Obj;

void ctor_obj(Obj *obj, const char *type, void *ptr);
void dtor_obj(Obj *obj);

int is_type(const Obj *obj, const char *type);

#endif // OBJ_H
