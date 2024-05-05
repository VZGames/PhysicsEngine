#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <stdlib.h>

typedef struct matrix_2d
{
    size_t w;
    size_t h;
    void* data;
} Mat2;

Mat2 create_matrix2d(size_t w, size_t h)
{
    return (Mat2) {w, h, malloc(w * h * sizeof(void*))};
}

void release_matrix2d(Mat2* matrix)
{
    free(matrix);
}

int index_at(Mat2* matrix, unsigned int x, unsigned int y)
{
    if (matrix == NULL) return -1;
    if (matrix->w > x && matrix->h > y)
    {
        return ((matrix->w * y) + x);
    }
    return -1;
}

void* item_at(Mat2* matrix, unsigned int x, unsigned int y)
{
    if (matrix != NULL && (matrix->w > x && matrix->h > y))
    {
        return (matrix + index_at(matrix, x, y));
    }
    return NULL;
}


#endif // MATRIX2D_H
