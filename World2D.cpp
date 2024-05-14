#include "World2D.h"
#include <stdlib.h>
#include <string.h>

World2D *CreateWorld(float g, unsigned char w, unsigned char h)
{
    World2D* world = (World2D*)malloc(sizeof(World2D));
    world->gravity = g;
    world->w = w;
    world->h = h;
    world->bodyBitset = (bool*)calloc(MAX_BODY, sizeof(bool));
    memset(&world->bodies[0], 0, sizeof(void*));
    return world;
}

void DestroyWorld(World2D *world)
{
    if (world != NULL)
    {
        free(world->bodyBitset);
        free(world);
        world = NULL;
    }
}

void Update(World2D *world, float deltatime, int totalIterations)
{
    (void)world;
    (void)deltatime;
    (void)totalIterations;
    for (int i = 0; i < totalIterations; ++i) {
        BroadPhase(world);
        NarrowPhase(world);
    }
}

void BroadPhase(World2D* world)
{
    for (unsigned char i = 0; i < (world->h * world->w); ++i) {

    }
}

void NarrowPhase(World2D* world)
{

}
