#include "Body2D.h"

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
        }
    }
    return body;
}

void DestroyBody(B2D *b)
{
    if (b != NULL)
    {
        b->world->OnBodyDestruction(b);
        free(b);
    }
}
