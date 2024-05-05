#ifndef BODY_H
#define BODY_H

#include "Math/Vector2D.h"

typedef enum e_body_type
{
    NOT_BODY,
    STATIC_BODY,
    DYNAMIC_BODY,
    KINEMATIC_BODY
} BodyType;

typedef struct body
{
    BodyType type;
    Vec2 position;
} Body;

Body* create_body();
void destroy_body(Body* body);
void body_set_type(Body* body, BodyType type);

#endif // BODY_H
