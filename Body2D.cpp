#include "Body2D.h"
#include <stdio.h>
#include <cstdlib>

BodyID CreateBody(W2D *w)
{
    int i;
    for (i = 0; i < MAX_BODY; ++i) {
        if (w->bits[i] == 0)
        {
            w->bits[i] = 1;
            w->bodies[i] = malloc(sizeof(B2D));
            break;
        }
    }
    return (BodyID) {i, w};
}

void DestroyBody(BodyID id)
{
    W2D* world = (W2D*)id.world;
    world->bits[id.index] = 0;
    free((void*)world->bodies[id.index]);
}
