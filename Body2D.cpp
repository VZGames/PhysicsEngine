#include "Body2D.h"
#include <stdio.h>
#include <cstdlib>
#include <Math/Shape2D.h>

Body2D* CreateBody(World2D *w, Body2D* define)
{
    for (int i = 0; i < MAX_BODY; ++i) {
        if (w->bodyBitset[i] == 0)
        {
            w->bodyBitset[i] = 1;
            Body2D* body = (Body2D*)malloc(sizeof(Body2D));
            body->index                     = i;
            body->position                  = define->position;
            body->density                   = define->density;
            body->linearVelocity            = define->linearVelocity;
            body->rotationVelocity          = define->rotationVelocity;
            body->rotation                  = define->rotation;
            body->restitution               = define->restitution;
            body->mass                      = define->mass;
            body->type                      = define->type;
            body->shape                     = define->shape;
            w->bodies[i] = body;
            return body;
        }
    }
    return NULL;
}

Shape2D* CreateShape(Body2D* target, ShapeType type, void* define)
{
    if (target->shape != NULL) return target->shape;
    Shape2D* shape = (Shape2D*)malloc(sizeof(Shape2D));
    target->shape = shape;
    target->shape->define = define;
    target->shape->type = type;
    return shape;

}

void DestroyBody(World2D* world, Body2D* body)
{
    world->bodyBitset[body->index] = 0;
    world->bodies[body->index] = NULL;
    free((void*)body->shape);
    free((void*)body);
}

Trans2D GetTransform(Body2D* target)
{
    return target->transform;
}

void SetTransform(Body2D* target, float x, float y, float angle)
{
    target->transform.x   = x;
    target->transform.y   = y;
    target->transform.cos = cos(angle);
    target->transform.sin = sin(angle);
}

void *GetShape(Body2D* body)
{
    return body->shape;
}
