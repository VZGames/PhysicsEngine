#include "Body2D.h"
#include <stdio.h>
#include <cstdlib>
#include <Math/Shape2D.h>

BID CreateBody(W2D *w, B2D* define)
{
    for (int i = 0; i < MAX_BODY; ++i) {
        if (w->bodyBitset[i] == 0)
        {
            w->bodyBitset[i] = 1;
            B2D* body = (B2D*)malloc(sizeof(B2D));

            body->position                  = define->position;
            body->density                   = define->density;
            body->linearVelocity            = define->linearVelocity;
            body->rotationVelocity          = define->rotationVelocity;
            body->rotation                  = define->rotation;
            body->restitution               = define->restitution;
            body->mass                      = define->mass;
            body->type                      = define->type;
            body->shapeId                   = define->shapeId;
            w->bodies[i] = body;
            return (BID) {i, w};
        }
    }
    return (BID) {-1, NULL};
}

SID CreateShape(W2D* world, BID target, ShapeType type, void* data)
{
    for (int i = 0; i < MAX_SHAPE; ++i) {
        if (world->shapeBitset[i] == 0)
        {
            world->shapeBitset[i] = 1;
            world->shapes[i] = malloc(sizeof(B2D));

            B2D* body = (B2D*)world->bodies[target.index];
            body->shapeId = (SID) {i, world};

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

            return body->shapeId;
        }
    }
    return (SID) {-1, NULL};

}

void DestroyBody(BID id)
{
    W2D* world = (W2D*)id.world;
    world->bodyBitset[id.index] = 0;
    free((void*)world->bodies[id.index]);
}

void DestroyShape(SID id)
{
    W2D* world = (W2D*)id.world;
    world->shapeBitset[id.index] = 0;
    free((void*)world->shapes[id.index]);
}

Trans2D GetTransform(BID target)
{
    W2D* world          = (W2D*)target.world;
    B2D* body           = (B2D*)world->bodies[target.index];
    return body->transform;
}

void SetTransform(BID target, float x, float y, float angle)
{
    W2D* world          = (W2D*)target.world;
    B2D* body           = (B2D*)world->bodies[target.index];
    body->transform.x   = x;
    body->transform.y   = y;
    body->transform.cos = cos(angle);
    body->transform.sin = sin(angle);
}
