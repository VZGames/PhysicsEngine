#ifndef SHAPE2D_H
#define SHAPE2D_H

#include "Vector2D.h"

typedef struct polygon
{
    Vec2* points;
    size_t count;
} Polygon;

typedef struct circle
{
    float radius;
    Vec2 center;
} Circle;

typedef struct ellipse
{
    float a;
    float b;
    Vec2 center;
} Ellipse;


#endif // SHAPE2D_H
