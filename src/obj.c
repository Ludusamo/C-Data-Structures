#include "obj.h"
#include <string.h>

int is_type(const Obj *obj, const char *type) {
	return strcmp(obj->type, type);
}
