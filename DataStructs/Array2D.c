#include "Array2D.h"

void CreateArray2D(Array2D *m, size_t w, size_t h)
{
    m->w = w;
    m->h = h;
    m->data = malloc(w * h * sizeof(void*));
}

int Array2DIndexAt(Array2D *m, unsigned int x, unsigned int y)
{
    if (m == NULL) return -1;
    if (m->w > x && m->h > y)
    {
        return (int)((m->w * y) + x);
    }
    return -1;
}

void *Array2DItemAt(Array2D *m, unsigned int x, unsigned int y)
{
    int index = Array2DIndexAt(m, x, y);
    if (index > -1)
    {
        return (m + index);
    }
    return NULL;
}
