#ifndef ARRAY1D_H
#define ARRAY1D_H

#include <stdlib.h>

typedef struct array_1d
{
    void** array;
    size_t size;
    size_t used;
} Array1D;

Array1D* CreateArray()
{
    Array1D* arr = (Array1D*)malloc(sizeof(Array1D));
    arr->used = 0;
    arr->size = 5;
    arr->array = (void**)malloc(sizeof(void*) * arr->size);
    return arr;
}

size_t SizeOfArr(Array1D* arr)
{
    return arr->used;
}

void Push(Array1D* arr, void* el)
{
    if (arr->used >= arr->size)
    {
        arr->size += 5;
        arr->array  = (void**)realloc(arr->array, arr->size);
    }
    arr->array[arr->used] = el;
    arr->used++;
}

void Delete(Array1D* arr, size_t index)
{
    for (size_t i = index; i < arr->size; ++i) {
        arr->array[i] = arr->array[i+1];
    }

    arr->used--;
    arr->size--;

    arr->array = (void**)realloc(arr->array, arr->size);
}

void Clear(Array1D* arr)
{
    free(arr);
}

#endif // ARRAY1D_H
