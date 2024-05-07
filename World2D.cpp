#include "World2D.h"
#include <stdlib.h>
#include <string.h>
#include "Math/Matrix2D.h"

W2D *CreateWorld(float g, float w, float h)
{
    W2D* world = (W2D*)malloc(sizeof(W2D));
    world->gravity = g;
    world->w = w;
    world->h = h;
    world->bodyBitset = (bool*)calloc(MAX_BODY, sizeof(bool));
    world->shapeBitset = (bool*)calloc(MAX_SHAPE, sizeof(bool));
    memset(&world->bodies[0], 0, sizeof(void*));
    memset(&world->shapes[0], 0, sizeof(void*));
    return world;
}

void DestroyWorld(W2D *world)
{
    if (world != NULL)
    {
        free(world->shapeBitset);
        free(world->bodyBitset);
        free(world);
        world = NULL;
    }
}

void Update(W2D *world, float deltatime, int totalIterations)
{
    (void)world;
    (void)deltatime;
    (void)totalIterations;
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
