#include "Body2D.h"
#include <stdio.h>
#include <cstdlib>

BodyID CreateBody(W2D *w, B2D* define)
{
    int i;
    for (i = 0; i < MAX_BODY; ++i) {
        if (w->body_bitset[i] == 0)
        {
            w->body_bitset[i] = 1;
            w->bodies[i] = malloc(sizeof(B2D));
            B2D* body = (B2D*)w->bodies[i];
            body->position                  = define->position;
            body->density                   = define->density;
            body->linearVelocity            = define->linearVelocity;
            body->rotationVelocity          = define->rotationVelocity;
            body->rotation                  = define->rotation;
            body->restitution               = define->restitution;
            body->mass                      = define->mass;
            body->shapes                    = define->shapes;
            body->type                      = define->type;
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
    switch (type) {
    case ShapeType::POLYGON:
    {
        Polygon* poly = (Polygon*)data;
        (void)poly;
        break;
    }
    case ShapeType::CIRCLE:
    {
        Circle* circle = (Circle*)data;
        (void)circle;
        break;
    }
    case ShapeType::ELLIPSE:
    {
        Ellipse* elip = (Ellipse*)data;
        (void)elip;
        break;
    }
    case ShapeType::CAPSULE:
    {
        Capsule* capsule = (Capsule*)data;
        (void)capsule;
        break;
    }
    default:
        break;
    }

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

    return (ShapeID) {i, body.index};
}
