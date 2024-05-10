#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include <math.h>

typedef struct transform_2d
{
    float x;
    float y;
    float cos;
    float sin;
} Trans2D;

void set_transform_2d(Trans2D* transform, float x, float y, float angle)
{
    transform->x    = x;
    transform->y    = y;
    transform->cos  = cos(angle);
    transform->sin  = sin(angle);
}

#endif // TRANSFORM2D_H
