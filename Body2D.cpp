#include "Body2D.h"
#include <stdio.h>
#include <cstdlib>
#include <Math/Shape2D.h>

BodyID CreateBody(W2D *w, B2D* define)
{
    int i;
    for (i = 0; i < MAX_BODY; ++i) {
        if (w->body_bitset[i] == 0)
        {
            w->body_bitset[i] = 1;
            B2D* body = (B2D*)malloc(sizeof(B2D));

            body->position                  = define->position;
            body->density                   = define->density;
            body->linearVelocity            = define->linearVelocity;
            body->rotationVelocity          = define->rotationVelocity;
            body->rotation                  = define->rotation;
            body->restitution               = define->restitution;
            body->mass                      = define->mass;
            body->shapes                    = define->shapes;
            body->type                      = define->type;

            w->bodies[i] = body;
            break;
        }
    }
    return (BodyID) {i, w};
}

void DestroyBody(BodyID id)
{
    W2D* world = (W2D*)id.world;
    world->body_bitset[id.index] = 0;
    free((void*)world->bodies[id.index]);
}

ShapeID CreateShape(BodyID body, ShapeType type, void* data)
{
    W2D* world = (W2D*)body.world;

    int i;
    for (i = 0; i < MAX_SHAPE; ++i) {
        if (world->shape_bitset[i] == 0)
        {
            world->shape_bitset[i] = 1;
            world->shapes[i] = malloc(sizeof(B2D));
            break;
        }
    }

    switch (type) {
    case ShapeType::POLYGON:
    {
        Polygon* define = (Polygon*)data;
        Polygon* shape  = (Polygon*)world->shapes[i];
        shape->count    = define->count;
        shape->points   = define->points;
        break;
    }
    case ShapeType::CIRCLE:
    {
        Circle* define  = (Circle*)data;
        Circle* shape   = (Circle*)world->shapes[i];
        shape->center   = define->center;
        shape->radius   = define->radius;
        break;
    }
    case ShapeType::ELLIPSE:
    {
        Ellipse* define = (Ellipse*)data;
        Ellipse* shape  = (Ellipse*)world->shapes[i];
        shape->a        = define->a;
        shape->b        = define->b;
        shape->center   = define->center;
        break;
    }
    case ShapeType::CAPSULE:
    {
        Capsule* define = (Capsule*)data;
        Capsule* shape  = (Capsule*)world->shapes[i];
        shape->center   = define->center;
        shape->height   = define->height;
        shape->radius   = define->radius;
        break;
    }
    default:
        break;
    }
    return (ShapeID) {i, body.index};
}
