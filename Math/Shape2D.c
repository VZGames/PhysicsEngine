#include "Shape2D.h"
#include <stdlib.h>

Polygon *CreatePolygon(Vec2 *vertices, size_t count)
{
    Polygon* shape = (Polygon*)malloc(sizeof(Polygon));
    shape->points = (Vec2*)malloc(count * sizeof(Vec2));
    for (size_t i = 0; i < count; ++i) {
        shape->points[i] = vertices[i];
    }
    shape->count = count;
    return shape;
}

Circle *CreateCircle(Vec2 center, float radius)
{
    Circle* shape = (Circle*)malloc(sizeof(Circle));
    shape->center = center;
    shape->radius = radius;
    return shape;
}

Ellipse *CreateEllipse(Vec2 center, float a, float b)
{
    Ellipse *shape = (Ellipse*)malloc(sizeof(Ellipse));
    shape->center   = center;
    shape->a        = a;
    shape->b        = b;
    return shape;
}

Capsule *CreateCapsule(Vec2 center, float height, float radius)
{
    Capsule *shape = (Capsule*)malloc(sizeof(Capsule));
    shape->center  = center;
    shape->height  = height;
    shape->radius  = radius;
    return shape;
}

float GetShapeArea(Shape2D shape)
{
    float area = 0.0f;
    switch (shape.type) {
    case CIRCLE:
    {
        Circle *circle = (Circle*)shape.define;
        area = (PI * (circle->radius * circle->radius));
        break;
    }
    case ELLIPSE:
    {
        Ellipse *ellipse = (Ellipse*)shape.define;
        area = (PI * (ellipse->a * ellipse->b));
        break;
    }
    case CAPSULE:
    {
        Capsule *capsule = (Capsule*)shape.define;
        float circle_area = (PI * (capsule->radius * capsule->radius));
        float rectangle_area = (2 * capsule->radius) * (2 * capsule->radius) * (capsule->height - 1);
        area = circle_area + rectangle_area;
        break;
    }
    case POLYGON:
    {
        Polygon *poly = (Polygon*)shape.define;
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
    return fabsf(area);
}
