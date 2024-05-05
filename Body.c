#include "Body.h"
#include <stdlib.h>

Body* create_body()
{
    return malloc(sizeof(Body));
}

void destroy_body(Body *body)
{
    free(body);
}

void body_set_type(Body *body, BodyType type)
{
    body->type = type;
}
