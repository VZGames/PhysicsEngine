#ifndef SHAPE2D_H
#define SHAPE2D_H

#include <stdint.h>
#include "Vector2D.h"
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

inline float area(ShapeType type, void* define)
{
    switch (type) {
    case CIRCLE:
    {
        Circle* circle = (Circle*)define;
        return (PI * (circle->radius * circle->radius));
    }
    case ELLIPSE:
    {
        Ellipse* ellipse = (Ellipse*)define;
        return (PI * (ellipse->a * ellipse->b));
    }
    case CAPSULE:
    {
        Capsule* capsule = (Capsule*)define;
        float circle_area = (PI * (capsule->radius * capsule->radius));
        float rectangle_area = (2 * capsule->radius) * (2 * capsule->radius) * (capsule->height - 1);
        return circle_area + rectangle_area;
    }
    case POLYGON:
    {
        Polygon* poly = (Polygon*)define;
        Vec2 G {0.0f, 0.0f};
        for (int i = 0; i < static_cast<size_t>(poly->count); ++i) {
            G.x += poly->points[i].x;
            G.y += poly->points[i].y;
        }
        G.x /= 2.0f;
        G.y /= 2.0f;



        break;
    }
    default:
        return 0.0f;
    }
    return 0.0f;
}
#endif // SHAPE2D_H
