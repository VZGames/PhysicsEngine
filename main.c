#include <stdio.h>
#include "World2D.h"
#include "Body2D.h"
#include "DataStructs/QuadTree.h"
#include "Utils.h"

void printList(void *data)
{
    Body2D *body = (Body2D*)data;
    printf("idx: %d\n", body->index);
}

void printArr(void *data)
{
    printf("%d\n", *(int*)data);
}

int main()
{
    World2D *world = CreateWorld(9.8f, 5, 3);

    Circle* circle = CreateCircle((Vec2) {0.0f, 0.0f}, 0.5f);
    struct QuadTree* tree = CreateQuadTreeNode("Root", world->w, world->h);

    for (int k = 0; k < 50; ++k) {
        Body2D body;
        body.type = STATIC_TYPE;
        body.density = 1.0f;
        body.mass = 1.0f;
        body.restitution = 0.3f;
        body.position = (Vec2) {
            randReal(0.0f, 5.0f),
            randReal(0.0f, 3.0f)
        };


        Body2D *obj = CreateBody(world, &body);
        printf("Object: %p with Position: (%f, %f)\n", obj, obj->position.x, obj->position.y);
        BodyCreateShape(obj, CIRCLE, circle);
        QuadtreeInsert(tree, obj, &obj->position, &obj->shape.boundary);
    }


    QuadTreeClear(tree);
    DestroyWorld(world);


    return 0;
}
