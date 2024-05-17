#ifndef BODY2D_H
#define BODY2D_H

#include "Math/Vector2D.h"
#include "Math/Shape2D.h"
#include "Math/Transform2D.h"
#include "World2D.h"

typedef enum
{
    STATIC_TYPE,
    DYNAMIC_TYPE,
    KINEMATIC_TYPE
} BodyType;

typedef struct
{
    int index;
    Vec2 position;
    Vec2 linearVelocity;

    float rotation;
    float rotationVelocity;

    BodyType type;
    Shape2D  shape;

    float mass;
    float density;
    float restitution;

    Trans2D transform;
} Body2D;

Body2D* CreateBody(World2D* world, Body2D* define);
Shape2D CreateShapeForBody(Body2D* target, ShapeType type, void* define);
Shape2D GetShape(Body2D* body);
void DestroyBody(World2D* world, Body2D* body);
Trans2D GetTransform(Body2D* target);
void SetTransform(Body2D* target, float x, float y, float angle);

#endif // BODY2D_H
