#ifndef ARRAY1D_H
#define ARRAY1D_H

#include <stdio.h>
#include <stdlib.h>

struct Array1D
{
    void* (*array);
    size_t capacity;
    size_t size;
};

struct Array1D* CreateArray1D();
void Array1DPush(struct Array1D* arr, void* el);
void Array1DInsert(struct Array1D* arr, void* el, size_t index);
void Array1DDelete(struct Array1D* arr, size_t index);
void ArrayTraverse(struct Array1D* arr, void(*cb)(void*));
inline void Array1DClear(struct Array1D* arr) { free(arr); }
inline size_t ArrayTotalSize(struct Array1D* arr) { return arr->size; }

#endif // ARRAY1D_H
