#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <stdlib.h>

typedef struct
{
    size_t w;
    size_t h;
    void* data;
} Array2D;

void CreateArray2D(Array2D* m, size_t w, size_t h);
int Array2DIndexAt(Array2D* m, unsigned int x, unsigned int y);
void* Array2DItemAt(Array2D* m, unsigned int x, unsigned int y);
inline size_t Array2DTotalCells(Array2D* m) { return (m->h * m->h); }
inline void Array2DClear(Array2D* m) { free(m); }


#endif // MATRIX2D_H
