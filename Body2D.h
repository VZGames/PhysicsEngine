#ifndef BODY2D_H
#define BODY2D_H

#include "Math/Vector2D.h"
#include "Math/Shape2D.h"
#include "Math/Transform2D.h"
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
    SID  shapeId;

    float mass;
    float density;
    float restitution;

    Trans2D transform;
} B2D;

BID CreateBody(W2D* world, B2D* define);
SID CreateShape(W2D* world, BID target, ShapeType type, void* define);
void DestroyBody(BID id);
Trans2D GetTransform(BID target);
void SetTransform(BID target, float x, float y, float angle);

#endif // BODY2D_H
