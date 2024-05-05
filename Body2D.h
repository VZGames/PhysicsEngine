#ifndef BODY2D_H
#define BODY2D_H

#include "Math/Vector2D.h"
#include "Math/Shape2D.h"
#include "World2D.h"

typedef enum e_body_type
{
    STATIC_TYPE,
    DYNAMIC_TYPE,
    KINEMATIC_TYPE
} BodyType;

typedef struct body_2d_define
{
    int index;
    W2D* world;
    Vec2 position;
    Vec2 linearVelocity;

    float rotation;
    float rotationVelocity;

    BodyType type;
    ShapeType shape;

    float mass;
    float density;
    float restitution;
} B2D;

B2D* CreateBody(W2D* world);
void DestroyBody(B2D* body);

#endif // BODY2D_H