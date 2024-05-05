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
    Vec2 center;
    float radius;
} Circle;

typedef struct ellipse
{
    Vec2 center;
    float a;
    float b;
} Ellipse;

typedef struct capsule
{
    Vec2 center;
    float height;
    float radius;
} Capsule;
#endif // SHAPE2D_H
