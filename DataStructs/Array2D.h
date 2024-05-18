#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <stdlib.h>

typedef struct
{
    size_t w;
    size_t h;
    void** data;
} Array2D;

Array2D* CreateArray2D(size_t w, size_t h);
int Array2DIndexAt(Array2D* arr, unsigned int x, unsigned int y);
void* Array2DItemAt(Array2D* arr, unsigned int x, unsigned int y);
void Array2DClear(Array2D* arr);
inline size_t Array2DTotalCells(Array2D* arr) { return (arr->h * arr->h); }


#endif // MATRIX2D_H