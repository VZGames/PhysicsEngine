#ifndef SHAPE2D_H
#define SHAPE2D_H

#include <stdint.h>
#include "Vector2D.h"
#include "Utils.h"
#define PI 3.14f

typedef enum e_shape_type
{
    POLYGON,
    CIRCLE,
    ELLIPSE,
    CAPSULE
} ShapeType;

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

inline float shape_area(ShapeType type, void* define)
{
    float area = 0.0f;
    switch (type) {
    case CIRCLE:
    {
        Circle* circle = (Circle*)define;
        area = (PI * (circle->radius * circle->radius));
        break;
    }
    case ELLIPSE:
    {
        Ellipse* ellipse = (Ellipse*)define;
        area = (PI * (ellipse->a * ellipse->b));
        break;
    }
    case CAPSULE:
    {
        Capsule* capsule = (Capsule*)define;
        float circle_area = (PI * (capsule->radius * capsule->radius));
        float rectangle_area = (2 * capsule->radius) * (2 * capsule->radius) * (capsule->height - 1);
        area = circle_area + rectangle_area;
        break;
    }
    case POLYGON:
    {
        Polygon* poly = (Polygon*)define;
        int j = (int)(poly->count) - 1;
        for (int i = 0; i < (int)(poly->count); ++i) {
            area += (poly->points[j].x + poly->points[i].x) * (poly->points[j].y - poly->points[i].y);
            j = i;
        }

        area *= 0.5f;
        break;
    }
    default:
        break;
    }
    return absf(area);
}


#endif // SHAPE2D_H
