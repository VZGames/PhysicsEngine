#include "World2D.h"
#include <stdlib.h>
#include <string.h>
#include "Body2D.h"

W2D *CreateWorld(float g, float w, float h)
{
    W2D* world = (W2D*)malloc(sizeof(W2D));
    world->gravity = g;
    world->w = w;
    world->h = h;
    world->bits = (bool*)calloc(MAX_BODY, sizeof(bool));
    memset(&world->bodies[0], 0, sizeof(void*));
    world->OnBodyDestruction = &BodyDestroyedCallback;
    return world;
}

void DestroyWorld(W2D *world)
{
    if (world != NULL)
    {
        free(world->bits);
        free(world);
    }
}

void Update(W2D *world, float deltatime, int totalIterations)
{
    for (int i = 0; i < totalIterations; ++i) {
        BroadPhase();
        NarrowPhase();
    }
}

void BroadPhase()
{

}

void NarrowPhase()
{

}


void BodyDestroyedCallback(void *data)
{
    B2D* body = (B2D*)data;
    for (int i = 0; i < MAX_BODY; ++i) {
        if (body->index == i)
        {
            body->world->bits[i] = 0;
            body->world->bodies[i] = NULL;
        }
    }
}
