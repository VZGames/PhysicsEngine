#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <stdlib.h>

typedef struct matrix_2d
{
    size_t w;
    size_t h;
    void* data;
} Mat2;

void create_matrix2d(Mat2* m, size_t w, size_t h)
{
    m->w = w;
    m->h = h;
    m->data = malloc(w * h * sizeof(void*));
}

void release_matrix2d(Mat2* m)
{
    free(m);
}

int index_at(Mat2* m, unsigned int x, unsigned int y)
{
    if (m == NULL) return -1;
    if (m->w > x && m->h > y)
    {
        return ((m->w * y) + x);
    }
    return -1;
}

void* item_at(Mat2* m, unsigned int x, unsigned int y)
{
    int index = index_at(m, x, y);
    if (index > -1)
    {
        return (m + index);
    }
    return NULL;
}


#endif // MATRIX2D_H
