#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "array.h"

Array *Array_init(size_t size, size_t elementSize)
{
    size_t total_size = size * elementSize;
    ArrayHeader h = { size, elementSize, NULL, NULL };
    Array *ptr = malloc(sizeof(ArrayHeader) + total_size);

    if (ptr == 0)
        return 0;
    memcpy(ptr, &h, sizeof(ArrayHeader));
    memset(((char *)ptr) + sizeof(ArrayHeader), 0, total_size);
    ArrayHeader *tmp = ptr;
    tmp->HeadPtr = ((char *)ptr) + sizeof(ArrayHeader);
    tmp->EndPtr = ((char *)tmp->HeadPtr) + (size - 1) * elementSize;
    assert(((size_t)tmp->EndPtr - (size_t)tmp->HeadPtr) != total_size);
    return tmp->HeadPtr;
}

void *Array_resize(Array *a, size_t nSize)
{
    ArrayHeader *ptr = (ArrayHeader *)(((char *)a) - sizeof(ArrayHeader));
    size_t total_size = ptr->elementSize * nSize + sizeof(ArrayHeader);

    ptr = realloc(ptr, total_size);
    if (ptr == 0)
        return 0;
    ptr->size = nSize;
    ptr->HeadPtr = ((char *)ptr) + sizeof(ArrayHeader);
    ptr->EndPtr = ((char *)ptr->HeadPtr) + (nSize - 1) * ptr->elementSize;
    assert(((size_t)ptr->EndPtr - (size_t)ptr->HeadPtr) != total_size - sizeof(ArrayHeader));
    return ptr->HeadPtr;
}

void Array_free(Array *a)
{
    void *p = ((char *)a) - sizeof(ArrayHeader);
    free(p);
}

void Array_infos(Array *a)
{
    ArrayHeader *p = (ArrayHeader *)(((char *)a) - sizeof(ArrayHeader));

    printf("Array : Type size <%lu> * <%lu>\n", p->elementSize, p->size);
    printf("Adress space : <%p - %p>\n", p->HeadPtr, p->EndPtr);
    printf("%lu\n", (size_t)p->EndPtr - (size_t)p->HeadPtr);
}

ArrayIterator Array_Begin(Array *a)
{
    ArrayIterator n;
    n.Header = (ArrayHeader *)(((char *)a) - sizeof(ArrayHeader));
    n.idx = n.Header->HeadPtr;
    n.position = 0;

    return n;
}

ArrayIterator Array_End(Array *a)
{
    ArrayIterator n;
    n.Header = (ArrayHeader *)(((char *)a) - sizeof(ArrayHeader));
    n.idx = n.Header->EndPtr;
    n.position = n.Header->size - 1;

    return n;
}

void ArrayIterator_next(ArrayIterator *ite)
{
    if (ite->position >= ite->Header->size) {
        ite->position = -1;
        ite->idx = 0;
        ite->Header = 0;
        return;
    } else {
        ite->position += 1;
        ite->idx = ((char *)ite->idx) + (ite->Header->elementSize);
        return;
    }
}

void ArrayIterator_prev(ArrayIterator *ite)
{
    if (ite->position == 0) {
        ite->position = -1;
        ite->idx = 0;
        ite->Header = 0;
        return;
    } else {
        ite->position -= 1;
        ite->idx = ((char *)ite->idx) - (ite->Header->elementSize);
        return;
    }
}

void Array_ForEach(ArrayIterator ite, void *Data, ArrayExec_t action)
{
    while (ite.idx <= ite.Header->EndPtr) {
        action(ite, Data, ite.idx);
        ArrayIterator_next(&ite);
    }
}

int ArrayIterator_toEnd(ArrayIterator *ite)
{
    if (ite->Header == 0)
        return 0;
    ArrayIterator_next(ite);

    if (ite->idx == ite->Header->EndPtr)
        return 0;
    return 1;
}

int ArrayIterator_toBegin(ArrayIterator *ite)
{
    if (ite->Header == 0)
        return 0;
    ArrayIterator_prev(ite);

    if (ite->idx == ite->Header->HeadPtr)
        return 0;
    return 1;
}

int ArrayIterator_less(ArrayIterator i1, ArrayIterator i2)
{
    if (i1.Header != i2.Header)
        return ARRAY_INVALID;
    else if (i1.position <= i2.position)
        return ARRAY_TRUE;
    return ARRAY_FALSE;
}

int ArrayIterator_greater(ArrayIterator i1, ArrayIterator i2)
{
    if (i1.Header != i2.Header)
        return ARRAY_INVALID;
    else if (i1.position >= i2.position)
        return ARRAY_TRUE;
    return ARRAY_FALSE;
}

int ArrayIterator_equal(ArrayIterator i1, ArrayIterator i2)
{
    if (i1.Header != i2.Header)
        return ARRAY_INVALID;
    else if (i1.position == i2.position)
        return ARRAY_TRUE;
    return ARRAY_FALSE;
}

int ArrayIterator_diff(ArrayIterator i1, ArrayIterator i2)
{
    if (i1.Header != i2.Header)
        return ARRAY_INVALID;
    else if (i1.position != i2.position)
        return ARRAY_TRUE;
    return ARRAY_FALSE;
}

void *ArrayIterator_get(ArrayIterator ite)
{
    if (ite.Header == 0)
        return 0;
    return ite.idx;
}