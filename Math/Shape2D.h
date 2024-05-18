#ifndef SHAPE2D_H
#define SHAPE2D_H

#include <stdint.h>
#include "Vector2D.h"
#define PI 3.14f

typedef enum
{
    POLYGON,
    CIRCLE,
    ELLIPSE,
    CAPSULE
} ShapeType;

typedef struct
{
    ShapeType type;
    void *define;
} Shape2D;

typedef struct
{
    Vec2 *points;
    size_t count;
} Polygon;

typedef struct
{
    Vec2 center;
    float radius;
} Circle;

typedef struct
{
    Vec2 center;
    float a;
    float b;
} Ellipse;

typedef struct
{
    Vec2 center;
    float height;
    float radius;
} Capsule;


Polygon *CreatePolygon(Vec2 *vertices, size_t count);
Circle *CreateCircle(Vec2 center, float radius);
Ellipse *CreateEllipse(Vec2 center, float a, float b);
Capsule *CreateCapsule(Vec2 center, float height, float radius);
float GetShapeArea(Shape2D shape);


#endif // SHAPE2D_H
