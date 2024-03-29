#include "value.h"
#include <assert.h>

int is_neg_zero(double d) {
    return (int) d == 0 && (*(uint64_t*) &d >> 63) == 1;
}

int is_bool(Value v) {
    return v.bits == true_val.bits || v.bits == false_val.bits;
}

int is_nil(Value v) {
    return v.bits == nil_val.bits;
}

int is_double(Value v) {
    return v.bits <= max_double;
}

int is_ptr(Value v) {
    return (v.bits & ptr_mask) == ptr_mask;
}

int is_int32(Value v) {
    return (v.bits & int_mask) == int_mask;
}

int is_obj(Value v) {
    return (v.bits & obj_mask) == obj_mask;
}

int is_fn(Value v) {
    return (v.bits & fn_mask) == fn_mask;
}

Value from_double(double d) {
    Value v;
    if (d == (int32_t) d && !is_neg_zero(d)) {
        v.bits = (uint64_t) (int32_t) d | int_mask;
        return v;
    }
    v.as_double = d;
    return v;
}

Value from_ptr(void *p) {
    uintptr_t p_i = (uintptr_t) p;
    assert((p_i & ptr_mask) == 0);
    return (Value) { .bits = p_i | ptr_mask };
}

Value from_obj(Obj *obj) {
    uintptr_t p_i = (uintptr_t) obj;
    assert((p_i & ptr_mask) == 0);
    return (Value) { .bits = p_i | obj_mask };
}

Value from_fn(void *p) {
    uintptr_t p_i = (uintptr_t) p;
    assert((p_i & ptr_mask) == 0);
    return (Value) { .bits = p_i | fn_mask };
}

void *get_ptr(Value v) {
    return (void*) (v.bits & ~ptr_mask);
}

Obj *get_obj(Value v) {
    return (Obj*) (v.bits & ~obj_mask);
}

void *get_fn(Value v) {
    return (void*) (v.bits & ~fn_mask);
}
