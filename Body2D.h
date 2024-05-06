#ifndef BODY2D_H
#define BODY2D_H

#include "Math/Vector2D.h"
#include "Math/Shape2D.h"
#include "World2D.h"
#include "ids.h"

typedef enum e_body_type
{
    STATIC_TYPE,
    DYNAMIC_TYPE,
    KINEMATIC_TYPE
} BodyType;

typedef struct body_2d_define
{
    Vec2 position;
    Vec2 linearVelocity;

    float rotation;
    float rotationVelocity;

    BodyType type;
    ShapeID* shapes;

    float mass;
    float density;
    float restitution;
} B2D;

BodyID CreateBody(W2D* world, B2D* define);
ShapeID CreateShape(BodyID body, ShapeType type, void* define);
void DestroyBody(BodyID id);

#endif // BODY2D_H
