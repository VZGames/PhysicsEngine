#include "Body2D.h"
#include <stdio.h>
#include <cstdlib>

B2D *CreateBody(W2D *w)
{
    B2D* body = NULL;
    for (int i = 0; i < MAX_BODY; ++i) {
        if (w->bits[i] == 0)
        {
            w->bits[i] = 1;
            w->bodies[i] = malloc(sizeof(B2D));
            body = (B2D*)w->bodies[i];
            body->index = i;
            body->world = w;
            break;
        }
    }
    return body;
}

void DestroyBody(B2D *body)
{
    if (body != NULL)
    {
        body->world->bits[body->index] = 0;
        free((void*)body);
        body = NULL;
    }
}
