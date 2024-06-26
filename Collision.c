#include "Collision.h"
#include "Math/Vector2D.h"
#include "Math/Shape2D.h"
#include "DataStructs/QuadTree.h"

bool IsCollisionCircle(Body2D *a, Body2D *b, void (*callback)(Body2D *, Body2D *))
{
    Circle* c1 = (Circle*)a->shape.define;
    Circle* c2 = (Circle*)b->shape.define;
    bool result = (Vec2Distance(a->position, b->position) <= (c1->radius + c2->radius));
    if (result)
    {
        callback(a, b);
    }

    return result;
}

void CollisionDetect(Array1D *nodeList, void (*callback)(Body2D *, Body2D *))
{

    for (int i = 0; i <= nodeList->size; i++) {
        struct QuadTree* node = (struct QuadTree*)Array1DItemAtIndex(nodeList, i);
        Array1D *objectList = node->objects;
        for (int j = 0; j <= node->objects->size; j++) {
            for (int k = i; k <= node->objects->size; k++) {
                Body2D* object_1 = (Body2D*)Array1DItemAtIndex(objectList, j);
                Body2D* object_2 = (Body2D*)Array1DItemAtIndex(objectList, j);

                IsCollisionCircle(object_1, object_2, callback);
            }
        }
    } 
}
