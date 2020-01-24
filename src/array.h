#pragma once

#include <stdlib.h>

typedef void Array;

typedef struct ArrayHeader {
    size_t size;
    size_t elementSize;
    Array *HeadPtr;
    Array *EndPtr;
} ArrayHeader;

typedef struct ArrayIterator {
    ArrayHeader *Header;
    Array *idx;
    size_t position;
} ArrayIterator;


enum ArrayIterator_ {
    ARRAY_INVALID = -1,
    ARRAY_TRUE,
    ARRAY_FALSE
};

typedef void (*ArrayExec_t)(ArrayIterator ite, void *Data, void *ArrayElement);

Array *Array_init(size_t size, size_t elementSize);
void Array_free(Array *a);
void Array_infos(Array *a);
void Array_ForEach(ArrayIterator ite, void *Data, ArrayExec_t action);
void *Array_resize(Array *, size_t);

ArrayIterator Array_Begin(Array *a);
ArrayIterator Array_End(Array *a);
void ArrayIterator_next(ArrayIterator *ite);
void ArrayIterator_prev(ArrayIterator *ite);
int ArrayIterator_toEnd(ArrayIterator *);
int ArrayIterator_toBegin(ArrayIterator *);

int ArrayIterator_less(ArrayIterator i1, ArrayIterator i2);
int ArrayIterator_greater(ArrayIterator i1, ArrayIterator i2);
int ArrayIterator_equal(ArrayIterator i1, ArrayIterator i2);
int ArrayIterator_diff(ArrayIterator i1, ArrayIterator i2);

void *ArrayIterator_get(ArrayIterator ite);
static inline size_t ArrayIterator_idx(ArrayIterator ite) { return ite.position; }