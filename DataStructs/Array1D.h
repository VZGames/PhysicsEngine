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

struct Array1D* CreateArray1D()
{
    struct Array1D* arr = (struct Array1D*)malloc(sizeof(struct Array1D));
    arr->size = 0;
    arr->capacity = 5;
    arr->array = malloc(sizeof(void*) * arr->capacity);
    return arr;
}

size_t ArrayTotalSize(struct Array1D* arr)
{
    return arr->size;
}

void Array1DPush(struct Array1D* arr, void* el)
{
    if (arr->size == arr->capacity)
    {
        arr->capacity += 5;
        void** temp = realloc(arr->array, (sizeof(void*) * arr->capacity));
        if (!temp)
        {
            fprintf(stderr, "ERROR: Couldn't realloc memory!\n");
            return;
        }
        arr->array  =  temp;
    }

    arr->array[arr->size] = el;
    arr->size++;
}

void Array1DInsert(struct Array1D* arr, void* el, size_t index)
{
    if (index < arr->size)
    {
        for (size_t i = arr->capacity; i > index; i--) {
            arr->array[i] = arr->array[i - 1];
        }
        arr->array[index] = el;
        arr->size++;
    }
    else // greater or equals  array size
    {
        Array1DPush(arr, el);
    }
}

void Array1DDelete(struct Array1D* arr, size_t index)
{
    for (size_t i = index; i < arr->capacity; ++i) {
        arr->array[i] = arr->array[i+1];
    }

    arr->size--;
    arr->capacity--;

    arr->array = (void*)realloc(arr->array, (sizeof(void*) * arr->capacity));
}

void Array1DClear(struct Array1D* arr)
{
    free(arr);
}

void ArrayTraverse(struct Array1D* arr, void(*cb)(void*))
{
    for (int i = 0; i < arr->size; ++i) {
        cb(arr->array[i]);
    }
}

#endif // ARRAY1D_H
